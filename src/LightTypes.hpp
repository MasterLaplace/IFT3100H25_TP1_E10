#pragma once

#include "ofMain.h"
#include <glm/glm.hpp>

// Classe pour la lumière ambiante
class AmbientLight {
public:
    glm::vec3 color;
    AmbientLight(const glm::vec3 &color);
    void apply();
};

// Classe pour la lumière directionnelle
class DirectionalLight {
public:
    glm::vec3 direction;
    glm::vec3 color;
    DirectionalLight(const glm::vec3 &direction, const glm::vec3 &color);
    void apply();
};

// Classe pour la lumière ponctuelle
class PointLight {
public:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
    PointLight(const glm::vec3 &position, const glm::vec3 &color, float intensity);
    void apply();
};

// Classe pour la lumière projecteur
class SpotLight {
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float cutoffAngle;
    float intensity;
    SpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float cutoffAngle,
              float intensity);
    void apply();
};

// Fonction utilitaire pour convertir glm::vec3 en ofFloatColor
ofFloatColor glmToOfColor(const glm::vec3 &color);

#pragma once