#pragma once

#include "Canvas.hpp"
#include "State.hpp"
#include "plugin/primitive/primitive.hpp"

namespace plugin::states {

class DrawPolygonState : public State {

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
    std::vector<glm::vec2> points;
};

} // namespace plugin::states
