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

void plugin::light::LightModel::begin(glm::vec3 lightPosition)
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
            lightShader->setUniform3f("lightPosition", lightPosition);
            break;

        case plugin::light::LightModel::Type::Phong:
            lightShader = &phong;
            lightShader->begin();
            lightShader->setUniform3f("color_ambient", _ambientColor);
            lightShader->setUniform3f("color_diffuse", _diffuseColor);
            lightShader->setUniform3f("lightPosition", lightPosition);
            lightShader->setUniform3f("color_specular", glm::vec3(1.0, 1.0, 1.0));
            lightShader->setUniform1f("brightness", 32.0);
            break;

        case plugin::light::LightModel::Type::BlinnPhong: lightShader = &blinnPhong; break;

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
