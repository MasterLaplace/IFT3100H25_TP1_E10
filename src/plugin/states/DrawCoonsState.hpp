#pragma once

#include "Canvas.hpp"
#include "State.hpp"
#include "plugin/topology/Coons.hpp"

namespace plugin::states {

    enum curveType {
    BEZIER,
    COONS
};

class DrawCoonsState : public State {
public:
    DrawCoonsState(curveType _type);

    void enter() override;
    void update() override;
    void draw() override;
    void exit() override;

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(Canvas *canvas) override;

    const curveType getCurveType() const;
    const ofPoint getSelectedPoint() const;
    const std::vector<ofPoint> getPoints() const;

    void setCurveType(curveType _type);
    void setPoint(ofPoint p);
    void setPoints(std::vector<ofPoint> p);

    void convertCurve();

private:
    curveType type;

    plugin::topology::Coons coons;
    plugin::topology::BezierQuadratique bezier;

    bool isDragging = false;
    ofPoint selectedPoint;

    void windowResized(int w, int h);
    bool isInside(ofPoint pointPos);
};

} // namespace plugin::states
