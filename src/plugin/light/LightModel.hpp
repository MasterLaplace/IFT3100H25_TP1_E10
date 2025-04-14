#pragma once

#include <glm/vec3.hpp>
#include <ofShader.h>

namespace plugin::light {

class LightModel {
public:
    enum class Type {
        None,
        Lambert,
        Phong,
        BlinnPhong
    };

    LightModel();

    // Getter pour les proprietes de la lumiere.
    Type getLightModel() const { return _model; }
    glm::vec3 getLightPosition() const { return _lightPosition; }
    glm::vec3 getAmbientColor() { return _ambientColor; }
    glm::vec3 getDiffuseColor() const { return _diffuseColor; }
    glm::vec3 getSpecularColor() const { return _specularColor; }

    // Setter pour les proprietes de la lumiere.
    void setLightModel(Type model) { _model = model; }
    void setLightPosition(const glm::vec3 &position) { _lightPosition = position; }
    void setAmbientColor(const glm::vec3 &color) { _ambientColor = color; }
    void setDiffuseColor(const glm::vec3 &color) { _diffuseColor = color; }
    void setSpecularColor(const glm::vec3 &color) { _specularColor = color; }

    // Setter pour les proprietes du materiau.
    void setMaterialAmbientColor(glm::vec3 color) { _materialAmbientColor = color; }
    void setMaterialDiffuseColor(glm::vec3 color) { _materialDiffuseColor = color; }
    void setMaterialSpecularColor(glm::vec3 color) { _materialSpecularColor = color; }
    void setShininess(float shininess) { _materialShininess = shininess; }

    void begin();
    void end();

private:
    // Les proprietes de l'eclairage.
    Type _model = Type::None;
    glm::vec3 _lightPosition{0.0, 0.0, 0.0};
    glm::vec3 _ambientColor{0.2, 0.2, 0.2};
    glm::vec3 _diffuseColor{0.8, 0.8, 0.8};
    glm::vec3 _specularColor{1.0, 1.0, 1.0};

    // Les proprietes du materiau.
    glm::vec3 _materialAmbientColor{0.0, 0.0, 0.0};
    glm::vec3 _materialDiffuseColor{0.2, 0.2, 0.2};
    glm::vec3 _materialSpecularColor{1.0, 1.0, 1.0};
    float _materialShininess = 32.0f;

    // Shader pour l'eclairage.
    ofShader lambert;
    ofShader phong;
    ofShader blinnPhong;

    // Pointeur vers le shader d'eclairage actif.
    ofShader *lightShader = nullptr;
};

} // namespace plugin::light
