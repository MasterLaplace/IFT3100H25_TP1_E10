#include "Canvas3D.hpp"

// Constructeur
Canvas3D::Canvas3D() { light.setGlobalPosition({0, 50, 0}); }

// Getter
plugin::light::LightModel::Type Canvas3D::getLightModel() { return lightModel.getLightModel(); }

glm::vec3 Canvas3D::getAmbientColor() { return lightModel.getAmbientColor(); }

glm::vec3 Canvas3D::getDiffuseColor() { return lightModel.getDiffuseColor(); }

// Setter
void Canvas3D::setLightModel(plugin::light::LightModel::Type model)
{
    lightModel.setLightModel(model);

    if (lightModel.getLightModel() == plugin::light::LightModel::Type::None)
    {
        light.disable();
        ofDisableLighting();
    }
    else
    {
        ofEnableLighting();
        light.enable();
    }
}

void Canvas3D::setAmbientColor(const glm::vec3 &color) { lightModel.setAmbientColor(color); }

void Canvas3D::setDiffuseColor(const glm::vec3 &color) { lightModel.setDiffuseColor(color); }

// Redefinition de la methode draw pour prendre en consideration la lumiere.
void Canvas3D::draw()
{
    ofBackground(backgroundColor);

    lightModel.begin(light.getPosition());

    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }

    lightModel.end();

    light.disable();
    ofDisableLighting();
}
