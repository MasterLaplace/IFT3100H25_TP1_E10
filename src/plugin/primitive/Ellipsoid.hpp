/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Ellipsoid
*/

#ifndef ELLIPSOID_HPP_
#define ELLIPSOID_HPP_

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Ellipsoid : public Primitive {
public:
    Ellipsoid(PrimitiveParams params, glm::vec3 radius, int numSlices, int numStacks);
    ~Ellipsoid() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

private:
    void drawFill();
    void drawOutline();

private:
    glm::vec3 _radius;
    int _numSlices;
    int _numStacks;
};

} // namespace plugin::primitive

#endif /* !ELLIPSOID_HPP_ */
