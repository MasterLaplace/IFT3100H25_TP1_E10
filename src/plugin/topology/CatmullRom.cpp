#include "CatmullRom.hpp"

plugin::topology::CatmullRom::CatmullRom(ofPoint P1, ofPoint P2, ofPoint P3, ofPoint P4)
{
    points.push_back(P1);
    points.push_back(P2);
    points.push_back(P3);
    points.push_back(P4);
}

const ofPoint plugin::topology::CatmullRom::getPoint() const
{
    if (selectedPoint == -1)
    {
        return ofPoint{-1, -1, -1};
    }

    return points[selectedPoint];
}

const ofPoint plugin::topology::CatmullRom::getPoint(int index) const
{
    if (index < 0 || index >= points.size())
    {
        std::cerr << "Erreur : CatmullRom::getPoint(int index) -> l'index est en dehors du vecteur points."
                  << std::endl;
        return ofPoint(-1, -1, -1);
    }

    return points[index];
}

const std::vector<ofPoint> plugin::topology::CatmullRom::getPoints() const { return points; }

const int plugin::topology::CatmullRom::getSelectedPoint() const { return selectedPoint; }

void plugin::topology::CatmullRom::setPoint(ofPoint p)
{
    if (selectedPoint < 0 || selectedPoint > points.size() - 1)
    {
        std::cerr << "Erreur : CatmullRom::setPoint() -> selectedPoint est en dehors des limites du vecteur points."
                  << std::endl;
        return;
    }
    points[selectedPoint] = p;
}

void plugin::topology::CatmullRom::setPoints(std::vector<ofPoint> p)
{
    if (p.size() <= 3)
    {
        std::cerr
            << "Erreur : CatmullRom::setPoints(std::vector<ofPoint> p) -> le vecteur p doit contenir au moins 4 points."
            << std::endl;
        return;
    }

    points = p;
}

void plugin::topology::CatmullRom::setSelectedPoint(int index)
{
    if (index < 0 || index > points.size() - 1)
    {
        std::cerr << "Erreur : CatmullRom::setSelectedPoint() -> index est en dehors des limites du vecteur points."
                  << std::endl;
        return;
    }
    selectedPoint = index;
}

void plugin::topology::CatmullRom::draw() const
{
    // On dessine la courbe
    ofSetColor(ofColor::black);

    for (int i = 0; i < points.size() - 3; ++i)
    {
        ofPoint prevPoint = nlerp(0.0f, i);
        for (float t = 0.01f; t < 1.0f; t += 0.01f)
        {
            ofPoint p = nlerp(t, i);
            ofDrawLine(prevPoint, p);
            prevPoint = p;
        }
    }

    // On dessine les points de controle.
    for (int i = 0; i < points.size(); ++i)
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

ofPoint plugin::topology::CatmullRom::catmullRom(float t, const ofPoint &p0, const ofPoint &p1, const ofPoint &p2,
                                                 const ofPoint &p3) const
{
    float t2 = t * t;
    float t3 = t * t * t;

    // Formule de Catmull-Rom generee par ChatGPT.
    return 0.5 * ((2.0 * p1) + (-p0 + p2) * t + (2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3) * t2 +
                  (-p0 + 3.0 * p1 - 3.0 * p2 + p3) * t3);
}

ofPoint plugin::topology::CatmullRom::nlerp(float t, int index) const
{
    if (points.size() < 4)
    {
        return ofPoint(0, 0);
    }

    if (index < 0 || index >= points.size() - 3)
    {
        return ofPoint(0, 0);
    }

    ofPoint p0 = points[index];
    ofPoint p1 = points[index + 1];
    ofPoint p2 = points[index + 2];
    ofPoint p3 = points[index + 3];

    if (t == 0.0f)
    {
        return p0;
    }

    if (t == 1.0f)
    {
        return p3;
    }

    return catmullRom(t, p0, p1, p2, p3);
}
