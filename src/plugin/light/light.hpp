#pragma once

#include "ofMain.h"
#include "LightModel.hpp"
#include "LightTypes.hpp"

namespace plugin::light {

class Light {
public:
    enum class lightType {
        NONE,
        AMBIENT,
        POINT_LIGHT,
        DIRECTIONAL,
        SPOT
    };

    Light(lightType type, plugin::light::LightModel::Type model);

    // Getter commun.
    glm::vec3 getLightPosition() { return _model.getLightPosition(); };

    // Getter pour le type.
    lightType getLightType() { return _type; };
    glm::vec3 getLightDirection();
    glm::vec3 getLightColor();
    float getCutOffAngle();
    float getIntensity();

    // Getter pour le modele.
    plugin::light::LightModel::Type getLightModel();
    glm::vec3 getAmbientColor() { return _model.getAmbientColor(); }
    glm::vec3 getDiffuseColor() { return _model.getDiffuseColor(); }
    glm::vec3 getSpecularColor() { return _model.getSpecularColor(); }

    // Setter commun.
    void setLightPosition(glm::vec3 lightPosition);

    // Setter pour le type.
    void setLightType(lightType type);
    void setLightDirection(glm::vec3 lightDirection);
    void setLightColor(glm::vec3 lightColor);
    void setLightAngle(float angle);
    void setLightIntensity(float intensity);

    // Setter pour le modele.
    void setLightModel(plugin::light::LightModel::Type model);
    void setAmbientColor(glm::vec3 ambientColor) { _model.setAmbientColor(ambientColor); }
    void setDiffuseColor(glm::vec3 diffuseColor) { _model.setDiffuseColor(diffuseColor); }
    void setSpecularColor(glm::vec3 specularColor) { _model.setSpecularColor(specularColor); }

    // Setter pour les proprietes du materiau.
    void setMaterialAmbientColor(glm::vec3 color) { _model.setMaterialAmbientColor(color); }
    void setMaterialDiffuseColor(glm::vec3 color) { _model.setMaterialDiffuseColor(color); }
    void setMaterialSpecularColor(glm::vec3 color) { _model.setMaterialSpecularColor(color); }
    void setShininess(float shininess) { _model.setShininess(shininess); }

    // Pour appliquer la lumiere.
    void apply();
    void close();

    int id;

private:
    // Le modele de lumiere. Celui-ci supporte son propre changement de type.
    plugin::light::LightModel _model;

    // Une variable pour pouvoir changer le type de lumiere.
    lightType _type;

    // On doit avoir une lumiere de chaque type parce que LightTypes est en fait plusieurs classes au lieu
    // d'etre une seule classe qui supporte un changement de type.
    glm::vec3 white{0, 0, 0};

    plugin::light::AmbientLight ambient = plugin::light::AmbientLight(white);
    plugin::light::DirectionalLight directional = plugin::light::DirectionalLight(glm::vec3(0, 0, 0), white);
    plugin::light::PointLight point = plugin::light::PointLight(glm::vec3(0, 0, 0), white, 1.0f);
    plugin::light::SpotLight spot = plugin::light::SpotLight(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), white, 1.0f, 1.0f);

    // Un pointeur sur le type de lumiere active.
    plugin::light::BaseLight *ptrType = nullptr;

    inline static uint32_t _nextId = 0;

    void updateLightType();

    // Fonction utilitaire pour convertir glm::vec3 en ofFloatColor
    ofFloatColor glmToOfColor(const glm::vec3 &color) { return ofFloatColor(color.r, color.g, color.b); }
};
} // namespace plugin::light
