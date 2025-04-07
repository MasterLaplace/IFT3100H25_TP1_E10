#pragma once

#include "State.hpp"
#include "plugin/topology/Coons.hpp"
#include "Canvas.hpp"

namespace plugin::states {

class DrawCoonsState : public State {
public:
    DrawCoonsState();

    void enter() override;
    void update() override;
    void draw() override;
    void exit() override;

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(Canvas *canvas) override;

    const ofPoint getSelectedPoint() const;
    const std::vector<ofPoint> getPoints() const;

    void setPoint(ofPoint p);
    void setPoints(std::vector<ofPoint> p);

private:
    plugin::topology::Coons coons;

    bool isDragging = false;
    ofPoint selectedPoint;

    void windowResized(int w, int h);
    bool isInside(ofPoint pointPos);
};

} // namespace plugin::states