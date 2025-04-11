#pragma once

#include "Canvas.hpp"
#include "plugin/light/light_header.hpp"
#include "plugin/topology/TessellationShader.hpp"

class Canvas3D : public Canvas {
public:
    Canvas3D();

    // Getter pour la lumiere.
    std::vector<plugin::light::Light *> getLights() { return lights; }
    plugin::light::LightModel::Type getLightModel(int i);
    plugin::light::Light::lightType getLightType(int i);
    int getLightId(int i);
    glm::vec3 getLightDirection(int i);
    glm::vec3 getLightPosition(int i);
    glm::vec3 getLightColor(int i);
    glm::vec3 &getAmbientColor(int i);
    glm::vec3 getDiffuseColor(int i);
    glm::vec3 getSpecularColor(int i);
    float getShininess(int i);
    float getLightAngle(int i);
    float getLightIntensity(int i);

    // Setter pour la lumiere.
    void setLightModel(plugin::light::LightModel::Type model, int i);
    void setLightType(plugin::light::Light::lightType lightType, int i);
    void setLightPosition(const glm::vec3 &position, int i);
    void setLightDirection(const glm::vec3 &lightDirection, int i);
    void setLightColor(const glm::vec3 &lightColor, int i);
    void setAmbientColor(const glm::vec3 &color, int i);
    void setDiffuseColor(const glm::vec3 &color, int i);
    void setSpecularColor(const glm::vec3 &color, int i);
    void setShininess(float shininess, int i);
    void setLightAngle(float angle, int i);
    void setLightIntensity(float intensity, int i);

    // Pour ajouter et supprimer des lumieres.
    void addLight(plugin::light::Light::lightType type, plugin::light::LightModel::Type model);
    void deleteLight(int i);

    // Fonction de dessin.
    void draw();

private:
    // liste de lumiere.
    std::vector<plugin::light::Light *> lights;

    // Shader de tessellation.
    TessellationShader tesShader;

    // Pour trouver une lumiere dans la liste.
    plugin::light::Light *getLight(int id);
};
