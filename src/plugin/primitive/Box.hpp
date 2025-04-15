#pragma once

#include "../geometry/BoundaryBox.hpp"
#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Box : public Primitive {
public:
    Box(PrimitiveParams params, glm::vec3 size);
    // Box(const Box &other);
    ~Box() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    void setSize(const glm::vec3 &size) { _size = size; }
    [[nodiscard]] glm::vec3 &getSize() { return _size; }

    glm::vec3 getAmbientColor() { return ambientColor; }
    glm::vec3 getDiffuseColor() { return diffuseColor; }
    glm::vec3 getSpecularColor() { return specularColor; }
    float getShininess() { return shininess; }

    void setAmbientColor(glm::vec3 newColor) { ambientColor = newColor; }
    void setDiffuseColor(glm::vec3 newColor) { diffuseColor = newColor; }
    void setSpecularColor(glm::vec3 newColor) { specularColor = newColor; }
    void setShininess(float newShininess) { shininess = newShininess; }
    void setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

private:
    void drawFill();
    void drawOutline();
    void drawBox();

private:
    glm::vec3 _size;
    // geometry::BoundaryBox bbox;

    // Attributs du materiau.
    glm::vec3 ambientColor = {0, 0, 0};
    glm::vec3 diffuseColor = {0, 0, 0};
    glm::vec3 specularColor = {0, 0, 0};
    float shininess = 32.0f;
};

} // namespace plugin::primitive
