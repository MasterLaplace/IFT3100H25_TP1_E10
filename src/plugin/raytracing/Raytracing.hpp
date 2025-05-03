/**************************************************************************
 * The implementation is based on the work of philvoyer, which can be
 * found in the following tutorial:
 * - https://github.com/philvoyer/IFT3100H25/blob/main/module09/EX01/IFT3100H25_Raytracer/raytracer.cpp
 **************************************************************************/

#pragma once

// c
#define _USE_MATH_DEFINES // pour M_PI avec compilateur de Visual Studio
#include <cmath>          // sqrt pow fabs cos sin

// c++
#include <fstream>
#include <iostream> // std cout endl
#include <sstream>  // stringstream

// c++11
#include <chrono>
#include <memory>
#include <random>
#include <vector>

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <glm/glm.hpp>

#include "../geometry/BoundaryBox.hpp"
#include "../primitive/primitives.hpp"

#include <algorithm>
#include <glm/glm.hpp>

#include "../../Node.hpp"

#include "../image/ResourceManager.hpp"
#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

namespace plugin::raytracing {

class Raytracing {
public:
    struct CreateInfo {
        glm::dvec3 position;
        glm::dvec3 direction;
        glm::dvec3 background_color;
        double fov;
        uint8_t depth;
        uint16_t width;
        uint16_t height;
        uint16_t ray_per_pixel;

        friend std::ostream &operator<<(std::ostream &os, const CreateInfo &info)
        {
            os << "Position: (" << info.position.x << ", " << info.position.y << ", " << info.position.z << ")\n"
               << "Direction: (" << info.direction.x << ", " << info.direction.y << ", " << info.direction.z << ")\n"
               << "Background Color: (" << info.background_color.x << ", " << info.background_color.y << ", " << info.background_color.z << ")\n"
               << "FOV: " << info.fov << "\n"
               << "Depth: " << static_cast<int>(info.depth) << "\n"
               << "Width: " << info.width << "\n"
               << "Height: " << info.height << "\n"
               << "Rays Per Pixel: " << info.ray_per_pixel;
            return os;
        }
    };

private:
    struct Vector {
        double x, y, z;

        constexpr Vector() : x(0.0), y(0.0), z(0.0) {}
        constexpr Vector(double x) : x(x), y(0.0), z(0.0) {}
        constexpr Vector(double x, double y) : x(x), y(y), z(0.0) {}
        constexpr Vector(double x, double y, double z) : x(x), y(y), z(z) {}
        constexpr Vector(const glm::dvec3 &v) : x(v.x), y(v.y), z(v.z) {}
        constexpr Vector(const glm::vec3 &v) : x(v.x), y(v.y), z(v.z) {}

        // produit scalaire (dot product)
        double dot(const Vector &v) const { return x * v.x + y * v.y + z * v.z; }

        // produit vectoriel (cross product)
        Vector cross(const Vector &v) const { return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

        // multiplication vectorielle
        Vector multiply(const Vector &v) const { return Vector(x * v.x, y * v.y, z * v.z); }

        // multiplication scalaire
        Vector operator*(double s) const { return Vector(x * s, y * s, z * s); }

        // multiplication élément par élément (vectorielle)
        Vector operator*(const Vector &v) const { return Vector(x * v.x, y * v.y, z * v.z); }

        // division vectorielle
        Vector operator/(const Vector &v) const { return Vector(x / v.x, y / v.y, z / v.z); }

        // division scalaire
        Vector operator/(double s) const { return Vector(x / s, y / s, z / s); }

        // addition vectorielle
        Vector operator+(const Vector &v) const { return Vector(x + v.x, y + v.y, z + v.z); }

        // soustraction vectorielle
        Vector operator-(const Vector &v) const { return Vector(x - v.x, y - v.y, z - v.z); }

        double operator[](size_t i) const
        {
            switch (i)
            {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return 0.0;
            }
        }

        // normalisation
        Vector &normalize() { return *this = *this * (1.0 / sqrt(x * x + y * y + z * z)); }
    };

    struct Ray {
        Vector origin;
        Vector direction;

        Ray(Vector o, Vector d) : origin(o), direction(d) {}
    };

    struct Camera {
        Vector position;
        Vector orientation;

        Vector axis_x;
        Vector axis_y;
        Vector axis_z;

        const uint16_t _VIEWPORT_WIDTH = 0;
        const uint16_t _VIEWPORT_HEIGHT = 0;

        const double _FOV = 0.0f;

        Camera(glm::dvec3 p, glm::dvec3 o, const uint16_t viewport_height, const uint16_t viewport_width,
               const double fov)
            : position(p), orientation(o), _VIEWPORT_WIDTH(viewport_width), _VIEWPORT_HEIGHT(viewport_height), _FOV(fov)
        {
            calibrate();
        }

        // fonction qui permet de calibrer la caméra en fonction la valeur courante de ses attributs
        void calibrate()
        {
            axis_z = orientation;
            axis_x = Vector(_VIEWPORT_WIDTH * _FOV / _VIEWPORT_HEIGHT);
            axis_y = axis_x.cross(axis_z).normalize() * _FOV;
        }
    };

public:
    Raytracing() = default;
    Raytracing(const CreateInfo &params, const std::vector<std::shared_ptr<primitive::Primitive>> &primitives)
        : _MAX_DEPTH(params.depth), _CAMERA_FOV(params.fov), _CAMERA_POSITION(params.position),
          _CAMERA_ORIENTATION(params.direction), _BACKGROUND_COLOR(params.background_color), _IMAGE_WIDTH(params.width),
          _IMAGE_HEIGHT(params.height), _RAY_PER_PIXEL(params.ray_per_pixel),
          _PIXEL_COUNT(params.width * params.height), _scene(primitives),
          _camera(params.position, params.direction, params.height, params.width, params.fov)
    {
        _pixels.reserve(_PIXEL_COUNT * 4u);
        _pixels.resize(_PIXEL_COUNT * 4u, 0);
    }

    inline void generate_image() noexcept
    {
        // rendu de la scène
        render();

        // procédure post-rendu (sauvegarde de l'image et désallocation de la mémoire)
        post_render();

        save_image_file();
    }

    inline void generate_image_async() noexcept
    {
        _is_rendering = true;
        std::thread([this]() {
            generate_image();
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _is_rendering = false;
            }
            _cv.notify_one();
        }).detach();
    }

    inline bool is_rendering() const noexcept { return _is_rendering; }

    inline void wait_for_rendering() noexcept
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this]() { return !_is_rendering; });
    }

    inline image::Image getImage() const noexcept
    {
        // créer une image à partir du tableau de pixels
        image::Image image;
        image.setUseTexture(false);
        image.getPixels().setFromPixels(reinterpret_cast<const unsigned char *>(_pixels.data()), _IMAGE_WIDTH,
                                        _IMAGE_HEIGHT, ofImageType::OF_IMAGE_COLOR_ALPHA);
        image.update();
        image.setUseTexture(true);

        return image;
    }

    void save_image_file()
    {
        // nom du fichier image de type .ppm (portable pixmap)
        std::stringstream ss;
        ss << "image" << _IMAGE_WIDTH << "x" << _IMAGE_HEIGHT << "_" << int(_RAY_PER_PIXEL) << ".ppm";
        std::string filename = ss.str();

        // déclaration et ouverture du fichier en mode écriture
        std::ofstream file;
        file.open(filename, std::ios::out);

        // entête du ficher pour une image avec un espace de couleur RGB 24 bits (P3 pour pixmap)
        file << "P3\n";

        // largeur et hauteur de l'image sur la seconde ligne de l'entête
        file << _IMAGE_WIDTH << ' ' << _IMAGE_HEIGHT << '\n';

        // valeur maximale de l'espace de couleur sur la troisième ligne de l'entête
        file << "255\n";

        // écriture des pixels dans le fichier image
        for (uint32_t index = 0; index < _PIXEL_COUNT; ++index)
        {
            // écrire la couleur du pixel dans le fichier image
            file << static_cast<std::uint32_t>(format_color_component(_pixels[index].x)) << " ";
            file << static_cast<std::uint32_t>(format_color_component(_pixels[index].y)) << " ";
            file << static_cast<std::uint32_t>(format_color_component(_pixels[index].z)) << " ";
        }

        // fermeture du fichier
        file.close();
    }

private:
    [[nodiscard]] inline double clamp(double x) const noexcept { return x < 0 ? 0 : x > 1 ? 1 : x; }

    [[nodiscard]] inline uint8_t format_color_component(double value) const noexcept
    {
        // clamp la valeur entre 0 et 1
        value = clamp(value);

        // appliquer la correction gamma
        value = pow(clamp(value), _GAMMA_CORRECTION);

        // convertir la valeur dans l'espace de couleur
        value = value * 255.0 + 0.5;

        // conversion numérique de réel vers entier
        return static_cast<uint8_t>(value);
    }

    [[nodiscard]] inline double intersect(const Ray &ray, const std::shared_ptr<primitive::Box> &box) const noexcept
    {
        double tmin = 0, tmax = std::numeric_limits<double>::infinity();

        for (uint8_t i = 0; i < 3; ++i)
        {
            double origin = (&ray.origin.x)[i];
            double dir = (&ray.direction.x)[i];
            double invD = 1.0 / dir;
            double t0 = (box->param.position[i] - origin) * invD;
            double t1 = (box->getSize()[i] - origin) * invD;

            if (invD < 0)
                std::swap(t0, t1);

            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;

            if (tmax <= tmin)
                return 0.0;
        }
        return tmin > 1e-4 ? tmin : 0.0;
    }

    [[nodiscard]] inline double intersect(const Ray &ray,
                                          const std::shared_ptr<primitive::Ellipsoid> &object) const noexcept
    {
        // distance de l'intersection la plus près si elle existe
        double distance = 0.0;

        // seuil de tolérance numérique du test d'intersection
        double epsilon = 1e-4f;

        // distance du point d'intersection
        double t = 0.0;

        // vecteur entre le centre de la sphère et l'origine du rayon
        Vector delta = Vector(object->param.position) - ray.origin;

        // calculer a
        double a = delta.dot(delta);

        // calculer b
        double b = delta.dot(ray.direction);

        // calculer c
        double c = object->getRadius().x * object->getRadius().y;

        // calculer le discriminant de l'équation quadratique
        double discriminant = b * b - a + c;

        // valider si le discriminant est négatif
        if (discriminant < 0)
        {
            // il n'y a pas d'intersection avec cette sphère
            return distance = 0;
        }

        // calculer la racine carrée du discriminant seulement si non négatif
        discriminant = sqrt(discriminant);

        // déterminer la distance de la première intersection
        t = b - discriminant;

        // valider si la distance de la première intersection est dans le seuil de tolérance
        if (t > epsilon)
            distance = t;
        else
        {
            // déterminer la distance de la première intersection
            t = b + discriminant;

            // valider si la distance de la seconde intersection est dans le seuil de tolérance
            distance = (t > epsilon) ? t : 0;
        }

        // retourner la distance du point d'intersection
        return distance;
    }

    [[nodiscard]] inline double intersect(const Ray &ray,
                                          const std::shared_ptr<primitive::Primitive> &primitive) const noexcept
    {
        if (dynamic_cast<primitive::Box *>(primitive.get()) != nullptr)
        {
            return intersect(ray, std::dynamic_pointer_cast<primitive::Box>(primitive));
        }
        else if (dynamic_cast<primitive::Ellipsoid *>(primitive.get()) != nullptr)
        {
            return intersect(ray, std::dynamic_pointer_cast<primitive::Ellipsoid>(primitive));
        }
        else if (dynamic_cast<primitive::ObjModel *>(primitive.get()) != nullptr)
        {
            // return intersect(ray, std::dynamic_pointer_cast<primitive::ObjModel>(primitive));
        }

        // primitive inconnue
        return 0.0;
    }

    void render() noexcept
    {
        // loop in scene
        for (auto &obj : _scene)
        {
            std::cout << "object : " << obj->param.position.x << ", " << obj->param.position.y << ", "
                      << obj->param.position.z << std::endl;
        }

        uint32_t index = 0;

        float progression = 0.0f;

        double r1, r2 = 0.0f;
        double dx, dy = 0.0f;

        Vector radiance;

        Vector distance;

        // itération sur les rangées de pixels
        for (uint16_t y = 0u; y < _IMAGE_HEIGHT; ++y)
        {
            // calculer le pourcentage de progression
            progression = 100.0f * y / (_IMAGE_HEIGHT - 1.0f);

            // afficher le pourcentage de progression du rendu dans la console
            fprintf(stderr, "\rraytracing (%d rays per pixel) : %4.1f %%", _RAY_PER_PIXEL, progression);

            // itération sur les colonnes de pixels
            for (uint16_t x = 0u; x < _IMAGE_WIDTH; ++x)
            {
                // déterminer l'index du pixel
                index = (_IMAGE_HEIGHT - y - 1) * _IMAGE_WIDTH + x;

                // itération sur les rangées du bloc de 2x2 échantillons
                for (uint8_t sy = 0u; sy < 2u; ++sy)
                {
                    // itération sur les colonnes du bloc de 2x2 échantillons
                    for (uint8_t sx = 0u; sx < 2u; ++sx)
                    {
                        // initialiser la radiance
                        radiance = Vector();

                        // itération des sur les rayons par pixel
                        for (uint16_t s = 0u; s < _RAY_PER_PIXEL; ++s)
                        {
                            // filtre de la tente
                            r1 = 2.0f * _random01(_rng);
                            dx = r1 < 1.0 ? sqrt(r1) - 1.0 : 1.0 - sqrt(2.0 - r1);

                            r2 = 2.0 * _random01(_rng);
                            dy = r2 < 1.0 ? sqrt(r2) - 1.0 : 1.0 - sqrt(2.0 - r2);

                            // calculer la distance de l'échantillon
                            distance = _camera.axis_x * (((sx + 0.5f + dx) / 2.0f + x) / _IMAGE_WIDTH - 0.5f) +
                                       _camera.axis_y * (((sy + 0.5f + dy) / 2.0f + y) / _IMAGE_HEIGHT - 0.5f) +
                                       _camera.axis_z;

                            // appel récursif du calcul de la radiance
                            radiance =
                                radiance +
                                compute_radiance(Ray(_camera.position + distance * 140.0, distance.normalize()), 0u) *
                                    (1.0 / _RAY_PER_PIXEL);
                        }

                        _pixels[index] =
                            _pixels[index] + Vector(clamp(radiance.x), clamp(radiance.y), clamp(radiance.z)) * 0.25;
                    }
                }
            }
        }

        std::cout << "\nrender done" << std::endl;
    }

    Vector compute_radiance(const Ray &ray, uint8_t depth)
    {
        // distance de l'intersection
        double distance = 0.0;

        // identifiant de la géométrie en intersection
        uint32_t id = 0;

        // valider s'il n'y a pas intersection
        if (!raycast(ray, distance, id))
            return Vector{}; // couleur par défault (noir)

        // référence sur une géométrie en intersection avec un rayon
        const auto &obj = _scene[id];

        // calculer les coordonnées du point d'intersection
        Vector x = ray.origin + ray.direction * distance;

        // attributs de l'objet touché
        Vector n;        // normale
        Vector emission; // emission
        Vector colour;   // couleur

        if (dynamic_cast<primitive::Ellipsoid *>(obj.get()) != nullptr)
        {
            n = (x - obj->param.position).normalize();
            emission = obj->param.emission;
            colour = Vector(obj->param.fillColor.r, obj->param.fillColor.g, obj->param.fillColor.b);
        }
        else if (dynamic_cast<primitive::Box *>(obj.get()) != nullptr)
        {
            // normale selon l'axe de la face impactée
            Vector d =
                x - Vector(obj->param.position + std::dynamic_pointer_cast<primitive::Box>(obj)->getSize()) * 0.5;
            double ax = fabs(d.x), ay = fabs(d.y), az = fabs(d.z);
            if (ax > ay && ax > az)
                n = Vector(d.x > 0 ? 1 : -1, 0, 0);
            else if (ay > az)
                n = Vector(0, d.y > 0 ? 1 : -1, 0);
            else
                n = Vector(0, 0, d.z > 0 ? 1 : -1);
            emission = obj->param.emission;
            colour = Vector(obj->param.fillColor.r, obj->param.fillColor.g, obj->param.fillColor.b);
        }
        else if (dynamic_cast<primitive::ObjModel *>(obj.get()) != nullptr)
        {
            // return intersect(ray, std::dynamic_pointer_cast<primitive::ObjModel>(primitive));
        }

        // ajustement de la direction de la normale
        Vector nl = n.dot(ray.direction) < 0 ? n : n * -1;

        // isoler la composante de couleur la plus puissante
        Vector f = Vector(obj->param.fillColor.r, obj->param.fillColor.g, obj->param.fillColor.b);
        double threshold = std::max(f.x, std::max(f.y, f.z));

        // valider si la limite du nombre de récursions est atteinte
        if (++depth > _MAX_DEPTH)
        {
            // test de probabilité
            if (_random01(_rng) < threshold)
                f = f * (1 / threshold);
            else
                return obj->param.emission;
        }

        if (obj->param.material == primitive::SurfaceType::DIFFUSE)
        {
            // matériau avec réflexion diffuse

            double r1 = 2.f * M_PI * _random01(_rng);
            double r2 = _random01(_rng);
            double r2s = sqrt(r2);

            Vector w = nl;
            Vector u = ((fabs(w.x) > 0.1 ? Vector(0, 1) : Vector(1)).cross(w)).normalize();
            Vector v = w.cross(u);
            Vector d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).normalize();

            return Vector(obj->param.emission) + f.multiply(compute_radiance(Ray(x, d), depth));
        }
        else if (obj->param.material == primitive::SurfaceType::SPECULAR)
        {
            // matériau avec réflexion spéculaire

            Vector refl_dir = ray.direction - n * 2.0 * n.dot(ray.direction);
            return emission + f.multiply(compute_radiance(Ray(x, refl_dir), depth));
        }
        else if (obj->param.material == primitive::SurfaceType::REFRACTION)
        {
            // matériau avec réflexion réfraction

            Ray reflection_ray(x, ray.direction - n * 2.0 * n.dot(ray.direction));

            bool into = n.dot(nl) > 0;

            double ior = 1.5; // indice de réfraction du verre
            double nc = 1.0;
            double nt = ior;
            double nnt = into ? nc / nt : nt / nc;
            double ddn = ray.direction.dot(nl);
            double cos2t;

            if ((cos2t = 1.0 - nnt * nnt * (1.0 - ddn * ddn)) < 0.0)
            {
                return Vector(obj->param.emission) + f.multiply(compute_radiance(reflection_ray, depth));
            }

            Vector tdir = (ray.direction * nnt - n * ((into ? 1.0 : -1.0) * (ddn * nnt + sqrt(cos2t)))).normalize();

            // effet de fresnel
            double a = nt - nc;
            double b = nt + nc;
            double R0 = a * a / (b * b);
            double c = 1.0 - (into ? -ddn : tdir.dot(n));
            double Re = R0 + (1.0 - R0) * c * c * c * c * c;
            double Tr = 1 - Re;
            double P = 0.25 + 0.5 * Re;
            double RP = Re / P;
            double TP = Tr / (1.0 - P);

            if (depth > 2)
            {
                if (_random01(_rng) < P)
                {
                    return emission + f.multiply(compute_radiance(reflection_ray, depth) * RP);
                }
                else
                {
                    return emission + f.multiply(compute_radiance(Ray(x, tdir), depth) * TP);
                }
            }

            return emission + f.multiply(compute_radiance(reflection_ray, depth) * Re +
                                         compute_radiance(Ray(x, tdir), depth) * Tr);
        }

        return Vector();
    }

    bool raycast(const Ray &ray, double &distance, uint32_t &id)
    {
        // variable temporaire pour la distance d'une intersection entre un rayon et une sphère
        double d = 0.0;

        // initialiser la distance à une valeur suffisamment éloignée pour qu'on la considère comme l'infinie
        distance = std::numeric_limits<double>::max();
        double infinity = distance;

        // nombre d'éléments dans la scène
        uint32_t n = static_cast<uint32_t>(_scene.size());

        // parcourir tous les éléments de la scène
        for (uint32_t index = 0; index < n; ++index)
        {
            // test d'intersection entre le rayon et la géométrie à cet index
            d = intersect(ray, _scene[index]);

            // valider s'il y a eu intersection et si la distance est inférieure aux autres intersections
            if (d && d < distance)
            {
                // nouvelle valeur courante de la distance et l'index de l'intersection la plus rapprochée de la caméra
                distance = d;
                id = index;
            }
        }

        // il y a eu intersection si la distance est plus petite que l'infini
        return distance < infinity;
    }

    void post_render() noexcept
    {
        _image.resize(_PIXEL_COUNT * 4u);

        for (uint32_t i = 0u; i < _PIXEL_COUNT; ++i)
        {
            _image[i * 4u + 0u] = format_color_component(_pixels[i].x);
            _image[i * 4u + 1u] = format_color_component(_pixels[i].y);
            _image[i * 4u + 2u] = format_color_component(_pixels[i].z);
            _image[i * 4u + 3u] = 255;
        }

        std::cout << "raytracer task is done" << std::endl;
    }

private:
    const uint8_t _MAX_DEPTH = 5u;
    const double _CAMERA_FOV = 0.5135; // ~30 degrés
    const Vector _CAMERA_POSITION = Vector(50, 50, 300);
    const Vector _CAMERA_ORIENTATION = Vector(0, -0.042612, -1).normalize();
    const Vector _BACKGROUND_COLOR = Vector(0.0, 0.0, 0.0);
    static constexpr double _GAMMA_CORRECTION = 1.f / 2.2f;

    // variables du programme
    const uint16_t _IMAGE_WIDTH = 0u;
    const uint16_t _IMAGE_HEIGHT = 0u;
    const uint8_t _RAY_PER_PIXEL = 0u;
    const uint32_t _PIXEL_COUNT = 0u;

    std::vector<std::shared_ptr<primitive::Primitive>> _scene;

    image::Image image{};
    std::vector<Vector> _pixels;
    std::vector<uint8_t> _image;
    Camera _camera;

    // source d'entropie
    std::random_device _rd;

    // générateur de nombres pseudo-aléatoires (algorithme mersenne twister)
    std::mt19937 _rng{_rd()};

    // distribution uniforme entre 0 et 1
    std::uniform_real_distribution<double> _random01{0.0, 1.0};

    std::atomic<bool> _is_rendering{false};
    std::mutex _mutex;
    std::condition_variable _cv;
};

} // namespace plugin::raytracing
