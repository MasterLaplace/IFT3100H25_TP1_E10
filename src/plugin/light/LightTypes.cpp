#include "LightTypes.hpp"

// Implémentation de la lumière ambiante
plugin::light::AmbientLight::AmbientLight(const glm::vec3 &color) : color(color) {}

void plugin::light::AmbientLight::apply() { ofSetGlobalAmbientColor(ofFloatColor(color.r, color.g, color.b)); }

// Implémentation de la lumière directionnelle
plugin::light::DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec3 &color)
    : direction(direction), color(color)
{
}

void plugin::light::DirectionalLight::apply()
{
    l.setDirectional();
    l.setOrientation(direction);
    l.setDiffuseColor(ofFloatColor(color.r, color.g, color.b));
    l.enable();
}

// Implémentation de la lumière ponctuelle
plugin::light::PointLight::PointLight(const glm::vec3 &position, const glm::vec3 &color, float intensity)
    : position(position), color(color), intensity(intensity)
{
}

void plugin::light::PointLight::apply()
{
    l.setPointLight();
    l.setPosition(position);
    l.setDiffuseColor(ofFloatColor(color.r, color.g, color.b));
    l.setAttenuation(1.0, 0.0, intensity); // Paramètres d'atténuation peuvent être changés ici
    l.enable();
}

// Implémentation de la lumière projecteur
plugin::light::SpotLight::SpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color,
                                    float cutoffAngle, float intensity)
    : position(position), direction(direction), color(color), cutoffAngle(cutoffAngle), intensity(intensity)
{
}

void plugin::light::SpotLight::apply()
{
    l.setSpotlight();
    l.setPosition(position);
    l.setOrientation(direction);
    l.setDiffuseColor(ofFloatColor(color.r, color.g, color.b));
    l.setSpotlightCutOff(cutoffAngle);
    l.setAttenuation(1.0, 0.0, intensity); // Paramètres d'atténuation peuvent être changés ici
    l.enable();
}

void plugin::light::BaseLight::close() { l.disable(); }
