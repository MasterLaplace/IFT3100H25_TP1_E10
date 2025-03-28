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
            lightShader->setUniform3f("color_ambient", _ambientColor);
            lightShader->setUniform3f("color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            break;

        case plugin::light::LightModel::Type::Phong:
            lightShader = &phong;
            lightShader->begin();
            lightShader->setUniform3f("color_ambient", _ambientColor);
            lightShader->setUniform3f("color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform3f("color_specular", _specularColor);
            lightShader->setUniform1f("brightness", _shininess);
            break;

        case plugin::light::LightModel::Type::BlinnPhong:
            lightShader = &blinnPhong;
            lightShader->begin();
            lightShader->setUniform3f("color_ambient", _ambientColor);
            lightShader->setUniform3f("color_diffuse", _diffuseColor);
            lightShader->setUniform3f("light_position", _lightPosition);
            lightShader->setUniform3f("color_specular", _specularColor);
            lightShader->setUniform1f("brightness", _shininess);
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
