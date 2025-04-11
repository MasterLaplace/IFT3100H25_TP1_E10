#pragma once

#include "ofMain.h"
#include <glm/glm.hpp>

namespace plugin::light {

class BaseLight {
public:
    ofLight l;
    virtual void apply() = 0;
    void close();
};

// Classe pour la lumière ambiante
class AmbientLight : public BaseLight {
public:
    glm::vec3 color;
    AmbientLight(const glm::vec3 &color);
    void apply() override;
};

// Classe pour la lumière directionnelle
class DirectionalLight : public BaseLight {
public:
    glm::vec3 color;
    glm::vec3 direction;
    DirectionalLight(const glm::vec3 &direction, const glm::vec3 &color);
    void apply() override;
};

// Classe pour la lumière ponctuelle
class PointLight : public BaseLight {
public:
    glm::vec3 color;
    glm::vec3 position;
    float intensity;
    PointLight(const glm::vec3 &position, const glm::vec3 &color, float intensity);
    void apply() override;
};

// Classe pour la lumière projecteur
class SpotLight : public BaseLight {
public:
    glm::vec3 color;
    glm::vec3 position;
    glm::vec3 direction;
    float cutoffAngle;
    float intensity;
    SpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float cutoffAngle,
              float intensity);
    void apply() override;
};
} // namespace plugin::light
