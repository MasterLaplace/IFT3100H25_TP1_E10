#pragma once

#include "Canvas.hpp"
#include "State.hpp"
#include "plugin/primitive/primitives.hpp"

namespace plugin::states {

class DrawEllipseState : public State {

public:
    void enter() override;
    void update() override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(Canvas* canvas) override;
    void draw() override;
    void exit() override;

private:
    void drawCursor();
    void drawPreview();
};

} // namespace plugin::states
