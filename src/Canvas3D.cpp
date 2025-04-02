#include "Canvas3D.hpp"

// Constructeur
Canvas3D::Canvas3D()
{
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    if (!tesShader.loadTessellation("tessellation_control_410.glsl", "tessellation_evaluation_410.glsl"))
        std::cerr << "Erreur dans le chargement du shader de None." << std::endl;
}

// Getter
plugin::light::LightModel::Type Canvas3D::getLightModel() { return lightModel.getLightModel(); }

glm::vec3 Canvas3D::getLightPosition() { return lightModel.getLightPosition(); }

glm::vec3 Canvas3D::getAmbientColor() { return lightModel.getAmbientColor(); }

glm::vec3 Canvas3D::getDiffuseColor() { return lightModel.getDiffuseColor(); }

glm::vec3 Canvas3D::getSpecularColor() { return lightModel.getSpecularColor(); }

float Canvas3D::getShininess() { return lightModel.getShininess(); }

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

void Canvas3D::setLightPosition(const glm::vec3 &position) { lightModel.setLightPosition(position); }

void Canvas3D::setAmbientColor(const glm::vec3 &color) { lightModel.setAmbientColor(color); }

void Canvas3D::setDiffuseColor(const glm::vec3 &color) { lightModel.setDiffuseColor(color); }

void Canvas3D::setSpecularColor(const glm::vec3 &color) { lightModel.setSpecularColor(color); }

void Canvas3D::setShininess(float shininess) { lightModel.setShininess(shininess); }

// Redefinition de la methode draw pour prendre en consideration la lumiere.
void Canvas3D::draw()
{
    ofBackground(backgroundColor);

    lightModel.begin();
    tesShader.begin();

    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }

    tesShader.end();
    lightModel.end();

    light.disable();
    ofDisableLighting();
}
