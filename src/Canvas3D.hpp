#pragma once

#include "Canvas.hpp"
#include "plugin/light/Light.hpp"
#include "plugin/topology/TessellationShader.hpp"

class Canvas3D : public Canvas {
public:
    Canvas3D();

    // Getter pour la lumiere.
    plugin::light::Light::ModelType getLightModel() { return light.getLightModel(); }
    plugin::light::Light::LightType getLightType() { return light.getLightType(); }
    glm::vec3 getLightDirection() { return light.getLightDirection(); }
    glm::vec3 getLightPosition() { return light.getLightPosition(); }
    glm::vec3 getAmbientColor() { return light.getAmbientColor(); }
    glm::vec3 getDiffuseColor() { return light.getDiffuseColor(); }
    glm::vec3 getSpecularColor() { return light.getSpecularColor(); }
    float getLightAngle() { return light.getLightAngle(); }
    float getLightRange() { return light.getLightRange(); }

    // Setter pour la lumiere.
    void setLightModel(plugin::light::Light::ModelType model) { light.setLightModel(model); }
    void setLightType(plugin::light::Light::LightType lightType) { light.setLightType(lightType); }
    void setLightPosition(const glm::vec3 &position) { light.setLightPosition(position); }
    void setLightDirection(const glm::vec3 &lightDirection) { light.setLightDirection(lightDirection); }
    void setAmbientColor(const glm::vec3 &color) { light.setAmbientColor(color); }
    void setDiffuseColor(const glm::vec3 &color) { light.setDiffuseColor(color); }
    void setSpecularColor(const glm::vec3 &color) { light.setSpecularColor(color); }
    void setLightAngle(float angle) { light.setLightAngle(angle); }
    void setLightRange(float range) { light.setLightRange(range); }

    // Setter pour la matrice de vue.
    void setViewMatrix(const glm::mat4 &viewMatrix) { light.setViewMatrix(viewMatrix); }

    // Fonction de dessin.
    void draw();

private:
    plugin::light::Light light;

    // Shader de tessellation.
    TessellationShader tesShader;

    glm::vec3 getMaterialAmbientColor(int i);
    glm::vec3 getMaterialDiffuseColor(int i);
    glm::vec3 getMaterialSpecularColor(int i);
    float getMaterialShininess(int i);
};
