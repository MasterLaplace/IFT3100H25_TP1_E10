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
    ~Ellipsoid() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    void setRadius(const glm::vec3 &radius) { _radius = radius; }
    [[nodiscard]] glm::vec3 &getRadius() { return _radius; }

private:
    void drawFill();
    void drawOutline();

private:
    glm::vec3 _radius;
    const int _numSlices = 50;
    const int _numStacks = 50;
    geometry::BoundaryBox bbox;
};

} // namespace plugin::primitive

#endif /* !ELLIPSOID_HPP_ */
