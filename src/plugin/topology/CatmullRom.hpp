#pragma once

#include "ofMain.h"

namespace plugin::topology {

class CatmullRom {
public:
    // Constructeur
    CatmullRom(ofPoint P1, ofPoint P2, ofPoint P3, ofPoint P4);

    // Getter
    const ofPoint getPoint() const;
    const ofPoint getPoint(int index) const;
    const std::vector<ofPoint> getPoints() const;
    const int getSelectedPoint() const;

    // Setter
    void setPoint(ofPoint p);
    void setPoints(std::vector<ofPoint> p);
    void setSelectedPoint(int index);

    // Fonction de dessin
    void draw() const;

    const float pointRadius = 15.0f;

private:
    int selectedPoint = -1;
    std::vector<ofPoint> points;

    ofPoint catmullRom(float t, const ofPoint &p0, const ofPoint &p1, const ofPoint &p2, const ofPoint &p3) const;
    ofPoint nlerp(float t, int index) const;
};

} // namespace plugin::topology
