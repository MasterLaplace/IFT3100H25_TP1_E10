#include "RaytracingScene.hpp"
#include <thread>

void RaytracingScene::setup(const raytracing::Raytracing::CreateInfo &params,
                            const std::vector<std::shared_ptr<primitive::Primitive>> &primitives)
{
    _scene = primitives;

    _position = params.position;
    _direction = params.direction;
    _background_color = params.background_color;
    _fov = params.fov;
    _depth = params.depth;
    _width = params.width;
    _height = params.height;
    _ray_per_pixel = params.ray_per_pixel;

    if (!_raytracer)
        _raytracer = std::make_unique<raytracing::Raytracing>(params, _scene);
    else if (!_raytracer->is_rendering())
    {
        _raytracer = std::make_unique<raytracing::Raytracing>(params, _scene);
    }
}

void RaytracingScene::draw()
{
    ofBackground(40);

    // std::cout << "RaytracingScene::draw() " << _image.isAllocated() << std::endl;

    if (!_raytracer->is_rendering() && !_image.isAllocated())
    {
        _image = _raytracer->getImage();
    }

    if (_image.isAllocated())
    {
        _image.draw(0, 0);
    }

    drawGui();
}

void RaytracingScene::drawGui()
{
    static int selected_primitive_index = -1; // Index de la primitive sélectionnée
    static bool use_cornell_box = false;      // Indicateur pour utiliser la Cornell Box
    bool modified = false;

    ImGui::Begin("Raytracing Controls");

    // Section: Actions
    if (ImGui::Button("Generate Image"))
    {
        if (!_raytracer->is_rendering())
        {
            _image.clear();
            _raytracer->generate_image_async();
        }
    }
    if (ImGui::Button("Export Image"))
    {
        if (_image.isAllocated())
        {
            exportImage("output.png");
        }
    }
    if (_raytracer->is_rendering())
    {
        ImGui::Text("Status: Rendering...");
    }
    else
    {
        ImGui::Text("Status: Rendering finished.");
    }
    ImGui::Separator();

    // Section: Cornell Box Toggle
    if (ImGui::Checkbox("Use Cornell Box", &use_cornell_box))
    {
        if (use_cornell_box)
        {
            init_cornell_box(); // Charger la Cornell Box
            modified = true;
        }
        else
        {
            _scene.clear(); // Réinitialiser la scène
        }
    }
    ImGui::Separator();

    // Section: Image Information
    ImGui::Text("Image Information");
    ImGui::Text("Size: %f x %f", _image.getWidth(), _image.getHeight());
    ImGui::Text("Number of primitives: %zu", _scene.size());
    ImGui::Separator();

    // Section: Scene Parameters
    ImGui::Text("Scene Parameters");
    if (ImGui::CollapsingHeader("Camera Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        glm::vec3 position = glm::vec3(_position);
        if (ImGui::DragFloat3("Position", &position.x, 0.1f))
        {
            _position = glm::dvec3(position);
            modified = true;
        }

        glm::vec3 direction = glm::vec3(_direction);
        if (ImGui::DragFloat3("Direction", &direction.x, 0.1f))
        {
            _direction = glm::dvec3(direction);
            modified = true;
        }

        float fov = static_cast<float>(_fov);
        if (ImGui::DragFloat("Field of View", &fov, 0.1f, 0.1f, 180.0f))
        {
            _fov = static_cast<double>(fov);
            modified = true;
        }
    }

    if (ImGui::CollapsingHeader("Rendering Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        glm::vec3 background_color = glm::vec3(_background_color);
        if (ImGui::ColorEdit3("Background Color", &background_color.x))
        {
            _background_color = glm::dvec3(background_color);
            modified = true;
        }

        ImGui::DragInt("Depth", reinterpret_cast<int *>(&_depth), 1, 1, 10);
        ImGui::SliderInt("Width", reinterpret_cast<int *>(&_width), 1, 4096, "%d", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderInt("Height", reinterpret_cast<int *>(&_height), 1, 4096, "%d", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderInt("Rays per Pixel", reinterpret_cast<int *>(&_ray_per_pixel), 1, 1024, "%d",
                         ImGuiSliderFlags_Logarithmic);
    }

    // Section: Primitives List
    if (!use_cornell_box && ImGui::CollapsingHeader("Primitives", ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (size_t i = 0; i < _scene.size(); ++i)
        {
            std::string label = "Primitive " + std::to_string(i);

            if (ImGui::Selectable(label.c_str(), selected_primitive_index == static_cast<int>(i)))
            {
                selected_primitive_index = static_cast<int>(i); // Mettre à jour l'index sélectionné
            }
        }
    }

    // Section: Selected Primitive Details
    if (!use_cornell_box && selected_primitive_index >= 0 && selected_primitive_index < static_cast<int>(_scene.size()))
    {
        const auto &selected_primitive = _scene[selected_primitive_index];
        glm::vec3 position = glm::vec3(selected_primitive->param.position);

        ImGui::Separator();
        ImGui::Text("Selected Primitive Details");
        if (ImGui::DragFloat3("Position", &position.x, 0.1f))
        {
            selected_primitive->param.position = glm::dvec3(position);
        }
        // Ajoutez ici d'autres propriétés si nécessaire
    }

    if (modified)
        updateScene();

    ImGui::End();
}

void RaytracingScene::updateScene()
{
    raytracing::Raytracing::CreateInfo param;
    param.position = {50, 50, 300};
    param.direction = glm::normalize(glm::vec3{0, -0.042612, -1});
    param.background_color = _background_color;
    param.fov = _fov;
    param.depth = static_cast<uint8_t>(_depth);
    param.width = static_cast<uint16_t>(_width);
    param.height = static_cast<uint16_t>(_height);
    param.ray_per_pixel = static_cast<uint16_t>(_ray_per_pixel);
    setup(param, _scene);
}

void RaytracingScene::init_cornell_box()
{
    constexpr double anchor = 1e5;
    constexpr double wall_radius = anchor;

    constexpr double box_size_x = 100.0;
    constexpr double box_size_y = 81.6;
    constexpr double box_size_z = 81.6;

    constexpr double box_x_min = 0.0;
    constexpr double box_x_max = box_size_x;
    constexpr double box_y_min = 0.0;
    constexpr double box_y_max = box_size_y;

    constexpr double box_center_x = (box_x_max - box_x_min) / 2.0;
    constexpr double box_center_y = (box_y_max - box_y_min) / 2.0;

    glm::dvec3 center(50.0, 40.0, 75.0);
    constexpr double half = 15.0;

    // vider la scène de son contenu
    _scene.clear();

    // génération du contenu de la scène
    _scene.insert(
        _scene.begin(),
        {
            // approximation d'une boîte de Cornell avec des sphères surdimensionnées qui simulent des
            // surfaces planes
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(box_center_x, anchor, box_size_z), glm::dvec3(0.),
                                           glm::dvec3(0.75), primitive::SurfaceType::DIFFUSE),
                glm::vec3(wall_radius)), // plancher
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(box_center_x, -anchor + box_size_y, box_size_z), glm::dvec3(0.),
                                           glm::dvec3(0.75), primitive::SurfaceType::DIFFUSE),
                glm::vec3(wall_radius)), // plafond
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(anchor + 1, box_center_y, box_size_z), glm::dvec3(0.),
                                           glm::dvec3(0.75, 0.25, 0.25), primitive::SurfaceType::DIFFUSE),
                glm::vec3(wall_radius)), // mur gauche
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(box_center_x, box_center_y, anchor), glm::dvec3(0.),
                                           glm::dvec3(0.25, 0.75, 0.25), primitive::SurfaceType::DIFFUSE),
                glm::vec3(wall_radius)), // mur arrière
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(-anchor + 99, box_center_y, box_size_z), glm::dvec3(0.),
                                           glm::dvec3(0.25, 0.25, 0.75), primitive::SurfaceType::DIFFUSE),
                glm::vec3(wall_radius)), // mur droit
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(box_center_x, box_center_y, -anchor + 170), glm::dvec3(0.),
                                           glm::dvec3(0.), primitive::SurfaceType::DIFFUSE),
                glm::vec3(wall_radius)), // mur avant

            // ensemble des sphères situées à l'intérieur de la boîte de Cornell
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(30, 30, 40), glm::dvec3(0.), glm::dvec3(1.),
                                           primitive::SurfaceType::SPECULAR),
                glm::vec3(22.5)), // sphère mirroir
            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(75, 40, 75), glm::dvec3(0.), glm::dvec3(1.),
                                           primitive::SurfaceType::REFRACTION),
                glm::vec3(17.5)), // sphère de verre

            std::make_shared<plugin::primitive::Ellipsoid>(
                primitive::PrimitiveParams(glm::dvec3(box_center_x, 600.0 + box_size_z - 0.27, box_size_z),
                                           glm::dvec3(15), glm::dvec3(0.), primitive::SurfaceType::DIFFUSE),
                glm::vec3(600)), // sphère lumineuse

            // ajoute un cube au milieu de la scène
            std::make_shared<plugin::primitive::Box>(
                primitive::PrimitiveParams(glm::dvec3(center.x - half, center.y - half, center.z - half),
                                           glm::dvec3(0.), glm::dvec3(0.8, 0.8, 0.2), primitive::SurfaceType::DIFFUSE),
                glm::dvec3(10)), // cube
        });
}

void RaytracingScene::exportImage(const std::string &filename)
{
    if (_image.isAllocated())
    {
        _image.save(filename);
        ofLogNotice() << "Image exported to " << filename;
    }
    else
    {
        ofLogError() << "No image to export.";
    }
}
