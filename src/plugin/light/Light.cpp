#include "Light.hpp"

plugin::light::Light::Light()
{
    if (lambertAmbient.load("lightning_330_vs.glsl", "lambert_ambient_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Lambert ambient." << std::endl;
    }

    if (lambertDirectionnal.load("lightning_330_vs.glsl", "lambert_directionnal_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Lambert directionnel." << std::endl;
    }

    if (lambertPointlight.load("lightning_330_vs.glsl", "lambert_pointlight_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Lambert ponctuelle." << std::endl;
    }

    if (lambertSpotlight.load("lightning_330_vs.glsl", "lambert_spotlight_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Lambert projecteur." << std::endl;
    }

    if (phongAmbient.load("lightning_330_vs.glsl", "phong_ambient_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Phong." << std::endl;
    }

    if (phongDirectionnal.load("lightning_330_vs.glsl", "phong_directionnal_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Phong directionnel." << std::endl;
    }

    if (phongPointlight.load("lightning_330_vs.glsl", "phong_pointlight_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Phong ponctuelle." << std::endl;
    }

    if (phongSpotlight.load("lightning_330_vs.glsl", "phong_spotlight_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Phong projecteur." << std::endl;
    }

    if (blinnPhongAmbient.load("lightning_330_vs.glsl", "blinn_phong_ambient_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Blinn-Phong ambiante." << std::endl;
    }

    if (blinnPhongDirectionnal.load("lightning_330_vs.glsl", "blinn_phong_directionnal_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Blinn-Phong directionnel." << std::endl;
    }

    if (blinnPhongPointlight.load("lightning_330_vs.glsl", "blinn_phong_pointlight_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Blinn-Phong ponctuelle." << std::endl;
    }

    if (blinnPhongSpotlight.load("lightning_330_vs.glsl", "blinn_phong_spotlight_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Blinn-Phong projecteur." << std::endl;
    }

    if (toon.load("lightning_330_vs.glsl", "toon_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader Toon." << std::endl;
    }
}

void plugin::light::Light::begin()
{
    switch (_model)
    {
    case plugin::light::Light::ModelType::Lambert:
        switch (_type)
        {
        case plugin::light::Light::LightType::Ambient:
            lightShader = &lambertAmbient;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            break;

        case plugin::light::Light::LightType::Directional:
            lightShader = &lambertDirectionnal;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_direction", _lightDirection);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            break;

        case plugin::light::Light::LightType::Pointlight:
            lightShader = &lambertPointlight;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform1f("light_range", _lightRange);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);

            // La matrice de vue.
            lightShader->setUniformMatrix4f("view_matrix", _viewMatrix);
            break;

        case plugin::light::Light::LightType::Spotlight:
            lightShader = &lambertSpotlight;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform3f("light_direction", _lightDirection);
            lightShader->setUniform1f("light_angle", _lightAngle);
            lightShader->setUniform1f("light_range", _lightRange);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            break;
        }
        break;

    case plugin::light::Light::ModelType::Phong:
        switch (_type)
        {
        case plugin::light::Light::LightType::Ambient:
            lightShader = &phongAmbient;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            break;

        case plugin::light::Light::LightType::Directional:
            lightShader = &phongDirectionnal;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_color_specular", _specularColor);
            lightShader->setUniform3f("light_direction", _lightDirection);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            lightShader->setUniform3f("material_color_specular", _materialSpecularColor);
            lightShader->setUniform1f("brightness", _materialShininess);
            break;

        case plugin::light::Light::LightType::Pointlight:
            lightShader = &phongPointlight;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_color_specular", _specularColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform1f("light_range", _lightRange);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            lightShader->setUniform3f("material_color_specular", _materialSpecularColor);
            lightShader->setUniform1f("brightness", _materialShininess);
            break;

        case plugin::light::Light::LightType::Spotlight:
            lightShader = &phongSpotlight;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_color_specular", _specularColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform3f("light_direction", _lightDirection);
            lightShader->setUniform1f("light_angle", _lightAngle);
            lightShader->setUniform1f("light_range", _lightRange);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            lightShader->setUniform3f("material_color_specular", _materialSpecularColor);
            lightShader->setUniform1f("brightness", _materialShininess);
            break;
        }
        break;

    case plugin::light::Light::ModelType::BlinnPhong:
        switch (_type)
        {
        case plugin::light::Light::LightType::Ambient:
            lightShader = &blinnPhongAmbient;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);

            // Les attributs du materiau.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            break;

        case plugin::light::Light::LightType::Directional:
            lightShader = &blinnPhongDirectionnal;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_color_specular", _specularColor);
            lightShader->setUniform3f("light_direction", _lightDirection);

            // Les attributs du materiau.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            lightShader->setUniform3f("material_color_specular", _materialSpecularColor);
            lightShader->setUniform1f("brightness", _materialShininess);
            break;

        case plugin::light::Light::LightType::Pointlight:
            lightShader = &blinnPhongPointlight;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_color_specular", _specularColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform1f("light_range", _lightRange);

            // Les attributs du materiau.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            lightShader->setUniform3f("material_color_specular", _materialSpecularColor);
            lightShader->setUniform1f("brightness", _materialShininess);
            break;

        case plugin::light::Light::LightType::Spotlight:
            lightShader = &blinnPhongSpotlight;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_color_specular", _specularColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform3f("light_direction", _lightDirection);
            lightShader->setUniform1f("light_angle", _lightAngle);
            lightShader->setUniform1f("light_range", _lightRange);

            // Les attributs du materiau.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            lightShader->setUniform3f("material_color_specular", _materialSpecularColor);
            lightShader->setUniform1f("brightness", _materialShininess);
            break;
        }
        break;

    // Si tout fonctionne je vais devoir ajouter les types de lumiere pour le modele Toon.
    case plugin::light::Light::ModelType::Toon:
        lightShader = &toon;
        lightShader->begin();

        // Les attributs de la lumiere.
        lightShader->setUniform3f("light_color_ambient", _ambientColor);
        lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
        lightShader->setUniform3f("light_position", _lightPosition);
        lightShader->setUniform3f("light_color_specular", _specularColor);

        // Les attributs du materiau.
        lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
        lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
        lightShader->setUniform3f("material_color_specular", _materialSpecularColor);
        lightShader->setUniform1f("brightness", _materialShininess);
        break;

    default: break;
    }
}

void plugin::light::Light::end() { lightShader->end(); }
