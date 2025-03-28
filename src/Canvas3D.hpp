#pragma once

#include "Canvas.hpp"
#include "ofLight.h"
#include "ofShader.h"
#include "plugin/light/light.hpp"

class Canvas3D : public Canvas {
public:
    Canvas3D();

    plugin::light::LightModel::Type getLightModel();
    glm::vec3 getLightPosition();
    glm::vec3 getAmbientColor();
    glm::vec3 getDiffuseColor();
    glm::vec3 getSpecularColor();
    float getShininess();

    void setLightModel(plugin::light::LightModel::Type model);
    void setLightPosition(const glm::vec3 &position);
    void setAmbientColor(const glm::vec3 &color);
    void setDiffuseColor(const glm::vec3 &color);
    void setSpecularColor(const glm::vec3 &color);
    void setShininess(float shininess);

    void draw();

private:
    // Modele de lumière.
    plugin::light::LightModel lightModel;

    // Lumière.
    ofLight light;

    ofSpherePrimitive sphere;
};
