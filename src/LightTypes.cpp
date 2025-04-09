#include "LightTypes.hpp"

// Fonction utilitaire pour convertir glm::vec3 en ofFloatColor
ofFloatColor glmToOfColor(const glm::vec3 &color) { return ofFloatColor(color.r, color.g, color.b); }

// Implémentation de la lumière ambiante
AmbientLight::AmbientLight(const glm::vec3 &color) : color(color) {}

void AmbientLight::apply() { ofSetGlobalAmbientColor(glmToOfColor(color)); }

// Implémentation de la lumière directionnelle
DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec3 &color)
    : direction(direction), color(color)
{
}

void DirectionalLight::apply()
{
    ofLight light;
    light.setDirectional();
    light.setOrientation(direction);
    light.setDiffuseColor(glmToOfColor(color));
    light.enable();
}

// Implémentation de la lumière ponctuelle
PointLight::PointLight(const glm::vec3 &position, const glm::vec3 &color, float intensity)
    : position(position), color(color), intensity(intensity)
{
}

void PointLight::apply()
{
    ofLight light;
    light.setPointLight();
    light.setPosition(position);
    light.setDiffuseColor(glmToOfColor(color));
    light.setAttenuation(1.0, 0.0, intensity); // Paramètres d'atténuation peuvent être changés ici
    light.enable();
}

// Implémentation de la lumière projecteur
SpotLight::SpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float cutoffAngle,
                     float intensity)
    : position(position), direction(direction), color(color), cutoffAngle(cutoffAngle), intensity(intensity)
{
}

void SpotLight::apply()
{
    ofLight light;
    light.setSpotlight();
    light.setPosition(position);
    light.setOrientation(direction);
    light.setDiffuseColor(glmToOfColor(color));
    light.setSpotlightCutOff(cutoffAngle);
    light.setAttenuation(1.0, 0.0, intensity); // Paramètres d'atténuation peuvent être changés ici
    light.enable();
}
