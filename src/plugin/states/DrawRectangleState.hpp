#pragma once

#include "Canvas.hpp"
#include "State.hpp"
#include "plugin/primitive/primitive.hpp"

#include <cmath>

namespace plugin::states {

class DrawRectangleState : public State {

public:
    void enter() override;
    void update() override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void draw() override;
    void exit() override;

private:
    void drawCursor();
    void drawPreview();
};

} // namespace plugin::states
