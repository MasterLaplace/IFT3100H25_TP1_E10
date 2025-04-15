#include "LightModel.hpp"

plugin::light::LightModel::LightModel()
{
    if (lambert.load("lightning_330_vs.glsl", "lambert_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Lambert." << std::endl;
    }

    if (phong.load("lightning_330_vs.glsl", "phong_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Phong." << std::endl;
    }

    if (blinnPhong.load("lightning_330_vs.glsl", "blinn_phong_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader de Blinn-Phong." << std::endl;
    }

    if (toon.load("lightning_330_vs.glsl", "toon_330_fs.glsl") == false)
    {
        std::cerr << "Erreur dans le chargement du shader Toon." << std::endl;
    }
}

void plugin::light::LightModel::begin()
{
    if (_model == Type::None)
    {
        lightShader = nullptr;
    }
    else
    {
        switch (_model)
        {
        case plugin::light::LightModel::Type::Lambert:
            lightShader = &lambert;
            lightShader->begin();

            // Les attributs de la lumiere.
            lightShader->setUniform3f("light_color_ambient", _ambientColor);
            lightShader->setUniform3f("light_color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_position", _lightPosition);

            // Les attributs du materiaux.
            lightShader->setUniform3f("material_color_ambient", _materialAmbientColor);
            lightShader->setUniform3f("material_color_diffuse", _materialDiffuseColor);
            break;

        case plugin::light::LightModel::Type::Phong:
            lightShader = &phong;
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

        case plugin::light::LightModel::Type::BlinnPhong:
            lightShader = &blinnPhong;
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
        case plugin::light::LightModel::Type::Toon:
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
}

void plugin::light::LightModel::end()
{
    if (_model != Type::None)
    {
        lightShader->end();
    }
}
