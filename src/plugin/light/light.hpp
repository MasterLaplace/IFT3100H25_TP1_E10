#pragma once

#include <glm/vec3.hpp>
#include <ofShader.h>
#include <ofLight.h>

namespace plugin::light {

class Light {
public:
    enum class ModelType {
        Lambert,
        Phong,
        BlinnPhong,
        Toon
    };

    enum class LightType {
        Ambient,
        Directional,
        Pointlight,
        Spotlight
    };

    Light();

    // Getter pour les proprietes de la lumiere.
    ModelType getLightModel() const { return _model; }
    LightType getLightType() const { return _type; }
    glm::vec3 getLightPosition() const { return _lightPosition; }
    glm::vec3 getLightDirection() const { return _lightDirection; }
    float getLightAngle() const { return _lightAngle; }
    float getLightRange() const { return _lightRange; }
    glm::vec3 getAmbientColor() { return _ambientColor; }
    glm::vec3 getDiffuseColor() const { return _diffuseColor; }
    glm::vec3 getSpecularColor() const { return _specularColor; }

    // Setter pour les proprietes de la lumiere.
    void setLightModel(ModelType model) { _model = model; }
    void setLightType(LightType type) { _type = type; }
    void setLightPosition(const glm::vec3 &position) { _lightPosition = position; }
    void setLightDirection(const glm::vec3 &direction) { _lightDirection = direction; }
    void setLightAngle(float angle) { _lightAngle = angle; }
    void setLightRange(float range) { _lightRange = range; }
    void setAmbientColor(const glm::vec3 &color) { _ambientColor = color; }
    void setDiffuseColor(const glm::vec3 &color) { _diffuseColor = color; }
    void setSpecularColor(const glm::vec3 &color) { _specularColor = color; }

    // Setter pour les proprietes du materiau.
    void setMaterialAmbientColor(glm::vec3 color) { _materialAmbientColor = color; }
    void setMaterialDiffuseColor(glm::vec3 color) { _materialDiffuseColor = color; }
    void setMaterialSpecularColor(glm::vec3 color) { _materialSpecularColor = color; }
    void setShininess(float shininess) { _materialShininess = shininess; }

    // Setter pour la matrice de vue.
    void setViewMatrix(const glm::mat4 &viewMatrix) { _viewMatrix = viewMatrix; }

    void begin();
    void end();

private:
    // Les proprietes de l'eclairage.
    ModelType _model = ModelType::Lambert;
    LightType _type = LightType::Ambient;
    
    glm::vec3 _lightPosition{0.0, 0.0, 0.0};
    glm::vec3 _ambientColor{0.2, 0.2, 0.2};
    glm::vec3 _diffuseColor{0.8, 0.8, 0.8};
    glm::vec3 _specularColor{1.0, 1.0, 1.0};
    glm::vec3 _lightDirection{0.0, 0.0, 1.0};
    float _lightAngle = 0.0f;
    float _lightRange = 50.0f;

    // Les proprietes du materiau.
    glm::vec3 _materialAmbientColor{0.0, 0.0, 0.0};
    glm::vec3 _materialDiffuseColor{0.2, 0.2, 0.2};
    glm::vec3 _materialSpecularColor{1.0, 1.0, 1.0};
    float _materialShininess = 32.0f;

    glm::mat4 _viewMatrix{1.0f};

    // Shader pour l'eclairage.
    ofShader lambertAmbient;
    ofShader lambertDirectionnal;
    ofShader lambertPointlight;
    ofShader lambertSpotlight;

    ofShader phongAmbient;
    ofShader phongDirectionnal;
    ofShader phongPointlight;
    ofShader phongSpotlight;

    ofShader blinnPhongAmbient;
    ofShader blinnPhongDirectionnal;
    ofShader blinnPhongPointlight;
    ofShader blinnPhongSpotlight;

    ofShader toon;

    // Pointeur vers le shader d'eclairage actif.
    ofShader *lightShader = nullptr;
};

} // namespace plugin::light
