/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Ellipsoid
*/

#ifndef ELLIPSOID_HPP_
#define ELLIPSOID_HPP_

#include "../geometry/BoundaryBox.hpp"
#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Ellipsoid : public Primitive {
public:
    Ellipsoid(PrimitiveParams params, glm::vec3 radius);
    Ellipsoid(const Ellipsoid &other) = default;
    Ellipsoid(Ellipsoid &&other) = default;
    ~Ellipsoid() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    void setRadius(const glm::vec3 &radius) { _radius = radius; }
    [[nodiscard]] const glm::vec3 &getRadius() const { return _radius; }

    std::shared_ptr<Primitive> clone() const override { return std::make_shared<Ellipsoid>(*this); }

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

private:
    glm::vec3 _radius;
    const int _numSlices = 50;
    const int _numStacks = 50;
    geometry::BoundaryBox bbox;

    // Attributs du materiau.
    glm::vec3 ambientColor = {0, 0, 0};
    glm::vec3 diffuseColor = {0, 0, 0};
    glm::vec3 specularColor = {0, 0, 0};
    float shininess = 32.0f;
};

} // namespace plugin::primitive

#endif /* !ELLIPSOID_HPP_ */
