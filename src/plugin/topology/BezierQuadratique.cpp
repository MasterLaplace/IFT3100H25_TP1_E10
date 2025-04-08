#include "BezierQuadratique.hpp"

namespace plugin::topology {
BezierQuadratique::BezierQuadratique(ofPoint c1, ofPoint c2)
{
    C1 = c1;
    C3 = c2;
    C2 = ofPoint((C1.x + C3.x) / 2, (C1.y + C3.y) / 2, (C1.z + C3.z) / 2);

    P1 = C1;
    P2 = (2.0f / 3.0f) * C2 + (1.0f / 3.0f) * C1;
    P3 = (1.0f / 3.0f) * C2 + (2.0f / 3.0f) * C3;
    P4 = C3;

    updatePoints();
}
BezierQuadratique::BezierQuadratique(ofPoint c1, ofPoint c2, ofPoint c3)
{
    C1 = c1;
    C2 = c2;
    C3 = c3;

    P1 = C1;
    P2 = (2.0f / 3.0f) * C2 + (1.0f / 3.0f) * C1;
    P3 = (1.0f / 3.0f) * C2 + (2.0f / 3.0f) * C3;
    P4 = C3;

    updatePoints();
}

const ofPoint BezierQuadratique::getC1() const { return C1; }

const ofPoint BezierQuadratique::getC2() const { return C2; }

const ofPoint BezierQuadratique::getC3() const { return C3; }

const ofPoint BezierQuadratique::getPoint() const
{
    if (isQuad)
    {
        switch (selectedPoint)
        {
        case -1: return ofPoint{-1, -1, -1}; break;
        case 0: return C1; break;
        case 1: return C2; break;
        case 2: return C3; break;
        default:
            std::cerr << "Erreur BezierQuadratique::getPoint() : index de point invalide (" << selectedPoint << ")."
                      << std::endl;
            return ofPoint{-1, -1, -1};
        }
    }
    else
    {
        switch (selectedPoint)
        {
        case -1: return ofPoint{-1, -1, -1}; break;
        case 0: return P1; break;
        case 1: return P2; break;
        case 2: return P3; break;
        case 3: return P4; break;
        default:
            std::cerr << "Erreur BezierCubic::getPoint() : index de point invalide (" << selectedPoint << ")."
                      << std::endl;
            return ofPoint{-1, -1, -1};
        }
    }
}

const ofPoint BezierQuadratique::getPoint(int index) const
{
    if (isQuad)
    {
        switch (index)
        {
        case 0: return C1; break;
        case 1: return C2; break;
        case 2: return C3; break;
        default:
            std::cerr << "Erreur BezierQuadratique::getPoint(int index) : index de point invalide (" << index << ")."
                      << std::endl;
            return ofPoint{-1, -1, -1};
        }
    }
    else
    {
        switch (index)
        {
        case 0: return P1; break;
        case 1: return P2; break;
        case 2: return P3; break;
        case 3: return P4; break;
        default:
            std::cerr << "Erreur BezierCubic::getPoint(int index) : index de point invalide (" << index << ")."
                      << std::endl;
            return ofPoint{-1, -1, -1};
        }
    }
}

const std::vector<ofPoint> BezierQuadratique::getPoints() const
{
    if (isQuad)
    {
        return pointsQuad;
    }
    else
    {
        return pointsCubic;
    }
}

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

void BezierQuadratique::setSelectedPoint(int index) { selectedPoint = index; }

void BezierQuadratique::setPoint(ofPoint p)
{
    if (isQuad)
    {
        switch (selectedPoint)
        {
        case 0: C1 = p; break;
        case 1: C2 = p; break;
        case 2: C3 = p; break;
        default:
            std::cerr << "Erreur BezierQuadratique::setPoint(ofPoint p) : index de point invalide (" << selectedPoint
                      << ")." << std::endl;
            break;
        }
    }
    else
    {
        switch (selectedPoint)
        {
        case 0: P1 = p; break;
        case 1: P2 = p; break;
        case 2: P3 = p; break;
        case 3: P4 = p; break;
        default:
            std::cerr << "Erreur BezierCubic::setPoint(ofPoint p) : index de point invalide (" << selectedPoint << ")."
                      << std::endl;
            break;
        }
    }

    updatePoints();
}

void BezierQuadratique::setPoints(const std::array<ofPoint, 3> p)
{
    C1 = p[0];
    C2 = p[1];
    C3 = p[2];
    updatePoints();
}

void BezierQuadratique::toCubic()
{
    if (isQuad)
    {
        P1 = C1;
        P2 = (2.0f / 3.0f) * C2 + (1.0f / 3.0f) * C1;
        P3 = (1.0f / 3.0f) * C2 + (2.0f / 3.0f) * C3;
        P4 = C3;
        isQuad = false;
    }
    updatePoints();
}

void BezierQuadratique::toQuadratic()
{
    if (!isQuad)
    {
        C1 = P1;
        C2 = (3.0f / 2.0f) * P2 - (1.0f / 2.0f) * P1;
        C3 = P4;
        isQuad = true;
    }
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

void BezierQuadratique::drawWithPoints(int precision) const
{
    draw(precision);

    std::vector<ofPoint> points;

    if (isQuad)
    {
        points = pointsQuad;
    }
    else
    {
        points = pointsCubic;
    }

    for (int i = 0; i < points.size(); i++)
    {
        if (i == selectedPoint)
        {
            ofSetColor(ofColor::green);
        }
        else
        {
            ofSetColor(ofColor::red);
        }
        ofDrawCircle(points[i], pointRadius);
    }
}

ofPoint BezierQuadratique::nlerpPoint(float t) const
{
    if (isQuad)
    {
        ofPoint p;
        p.x = nlerpQuad(C1.x, C2.x, C3.x, t);
        p.y = nlerpQuad(C1.y, C2.y, C3.y, t);
        p.z = nlerpQuad(C1.z, C2.z, C3.z, t);
        return p;
    }
    else
    {
        ofPoint p;
        p.x = nlerpCubic(P1.x, P2.x, P3.x, P4.x, t);
        p.y = nlerpCubic(P1.y, P2.y, P3.y, P4.y, t);
        p.z = nlerpCubic(P1.z, P2.z, P3.z, P4.z, t);
        return p;
    }
}

void BezierQuadratique::updatePoints()
{
    pointsQuad = {C1, C2, C3};
    pointsCubic = {P1, P2, P3, P4};
}

float BezierQuadratique::nlerpQuad(float a, float b, float c, float t) const
{
    return pow(1 - t, 2) * a + 2 * (1 - t) * t * b + pow(t, 2) * c;
}
float BezierQuadratique::nlerpCubic(float a, float b, float c, float d, float t) const
{
    return pow((1 - t), 3) * a + 3 * pow((1 - t), 2) * t * b + 3 * (1 - t) * pow(t, 2) * c + pow(t, 3) * d;
}
} // namespace plugin::topology
