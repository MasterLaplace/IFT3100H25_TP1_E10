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

    Type getLightModel() const { return _model; }
    glm::vec3 getAmbientColor() { return _ambientColor; }
    glm::vec3 getDiffuseColor() const { return _diffuseColor; }

    void setLightModel(Type model) { _model = model; }
    void setAmbientColor(const glm::vec3 &color) { _ambientColor = color; }
    void setDiffuseColor(const glm::vec3 &color) { _diffuseColor = color; }

    void begin(glm::vec3 lightPosition);
    void end();

private:
    // Les proprietes de l'eclairage.
    Type _model = Type::None;
    glm::vec3 _ambientColor{0.2, 0.2, 0.2};
    glm::vec3 _diffuseColor{0.8, 0.8, 0.8};

    // Shader pour l'eclairage.
    ofShader lambert;
    ofShader phong;
    ofShader blinnPhong;

    // Pointeur vers le shader d'eclairage actif.
    ofShader *lightShader = nullptr;
};

} // namespace plugin::light
