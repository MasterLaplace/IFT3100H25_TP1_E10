#pragma once

#include "ofMain.h"
#include "ofPoint.h"
#include <array>

namespace plugin::topology {

class BezierQuadratique {
public:
    BezierQuadratique(ofPoint c1, ofPoint c2);
    BezierQuadratique(ofPoint c1, ofPoint c2, ofPoint c3);

    // Getter
    const ofPoint getC1() const;
    const ofPoint getC2() const;
    const ofPoint getC3() const;
    const ofPoint getPoint() const;
    const ofPoint getPoint(int index) const;
    const std::vector<ofPoint> getPoints() const;

    // Setter
    void setC1(const ofPoint p);
    void setC2(const ofPoint p);
    void setC3(const ofPoint p);
    void setSelectedPoint(int index);
    void setPoint(ofPoint p);
    void setPoints(const std::array<ofPoint, 3> p);

    // Conversion entre quadratique et cubique
    void toCubic();
    void toQuadratic();

    void draw(int precision) const;
    void drawWithPoints(int precision) const;
    ofPoint nlerpPoint(float t) const;

    bool isQuad = true;
    float pointRadius = 15.0f;

private:
    // Les points de controle quadratiques.
    ofPoint C1;
    ofPoint C2;
    ofPoint C3;
    
    // Les points de controle cubiques.
    ofPoint P1;
    ofPoint P2;
    ofPoint P3;
    ofPoint P4;

    // Les listes des points de controle.
    std::vector<ofPoint> pointsQuad;
    std::vector<ofPoint> pointsCubic;

    int selectedPoint = -1;

    void updatePoints();
    float nlerpQuad(float a, float b, float c, float t) const;
    float nlerpCubic(float a, float b, float c, float d, float t) const;
};
} // namespace plugin::topology
