#pragma once

#include "ofMain.h"
#include "ofPoint.h"
#include <array>

namespace plugin::topology {

class BezierQuadratique {
public:
    BezierQuadratique(ofPoint c1, ofPoint c2, ofPoint c3);

    // Getter
    const ofPoint getC1() const;
    const ofPoint getC2() const;
    const ofPoint getC3() const;
    const std::array<ofPoint, 3> getPoints() const;

    // Setter
    void setC1(const ofPoint p);
    void setC2(const ofPoint p);
    void setC3(const ofPoint p);
    void setPoints(const std::array<ofPoint, 3> p);

    void draw(int precision) const;
    ofPoint nlerpPoint(float t) const;

private:
    ofPoint C1;
    ofPoint C2;
    ofPoint C3;

    std::array<ofPoint, 3> points;

    void updatePoints();
    float nlerp(float a, float b, float c, float t) const;
};
} // namespace plugin::topology
