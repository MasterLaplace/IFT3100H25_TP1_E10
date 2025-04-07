#pragma once

#include "BezierQuadratique.hpp"
#include "ofMain.h"

namespace plugin::topology {

class Coons {
public:
    // Constructeur.
    Coons(ofPoint c1, ofPoint c2, ofPoint c3, ofPoint c4);

    // Getter.
    const ofPoint getPoint(int index) const;
    const ofPoint getPoint() const;
    const std::vector<ofPoint> getPoints() const;

    // Setter.
    void setPoint(ofPoint p, int index);
    void setPoint(ofPoint p);
    void setSelectedPoint(int index);
    void setPoints(std::vector<ofPoint> p);

    // Fonction de dessin.
    void draw();

    const float pointRadius = 15.0f;

private:
    // Les courbes de beziers.
    BezierQuadratique curve1;
    BezierQuadratique curve2;
    BezierQuadratique curve3;
    BezierQuadratique curve4;

    // Un vecteur qui contient tous les points.
    std::vector<ofPoint> points;

    int selectedPoint = -1;

    // Fonctions d'interpolations.
    ofPoint blerp(float u, float v);
    ofPoint lerpu(float u, float v);
    ofPoint lerpv(float u, float v);
    ofPoint surfaceCoons(float u, float v);

    // Fonctions de mise a jour.
    void updatePoints();
    void updateCurves();
};
} // namespace plugin::topology
