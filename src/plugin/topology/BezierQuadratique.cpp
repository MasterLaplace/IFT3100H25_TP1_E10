#include "BezierQuadratique.hpp"

namespace plugin::topology {

BezierQuadratique::BezierQuadratique(ofPoint c1, ofPoint c2, ofPoint c3)
{
    C1 = c1;
    C2 = c2;
    C3 = c3;

    updatePoints();
}

const ofPoint BezierQuadratique::getC1() const { return C1; }

const ofPoint BezierQuadratique::getC2() const { return C2; }

const ofPoint BezierQuadratique::getC3() const { return C3; }

const std::array<ofPoint, 3> BezierQuadratique::getPoints() const { return points; }

void BezierQuadratique::setC1(const ofPoint p)
{
    C1 = p;
    updatePoints();
}

void BezierQuadratique::setC2(const ofPoint p)
{
    C2 = p;
    updatePoints();
}

void BezierQuadratique::setC3(const ofPoint p)
{
    C3 = p;
    updatePoints();
}

void BezierQuadratique::setPoints(const std::array<ofPoint, 3> p)
{
    C1 = p[0];
    C2 = p[1];
    C3 = p[2];
    updatePoints();
}

void BezierQuadratique::draw(int precision) const
{
    ofSetColor(ofColor::black);
    for (int i = 0; i < precision; i++)
    {
        float t1 = (float) i / (float) precision;
        float t2 = (float) (i + 1) / (float) precision;
        ofPoint p1 = nlerpPoint(t1);
        ofPoint p2 = nlerpPoint(t2);
        ofDrawLine(p1, p2);
    }
}

ofPoint BezierQuadratique::nlerpPoint(float t) const
{
    ofPoint p;
    p.x = nlerp(C1.x, C2.x, C3.x, t);
    p.y = nlerp(C1.y, C2.y, C3.y, t);
    p.z = nlerp(C1.z, C2.z, C3.z, t);
    return p;
}

void BezierQuadratique::updatePoints() { points = {C1, C2, C3}; }

float BezierQuadratique::nlerp(float a, float b, float c, float t) const
{
    return pow(1 - t, 2) * a + 2 * (1 - t) * t * b + pow(t, 2) * c;
}
} // namespace plugin::topology
