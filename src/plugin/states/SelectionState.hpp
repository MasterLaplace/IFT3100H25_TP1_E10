#pragma once

#include "Canvas.hpp"
#include "State.hpp"
#include "ofMain.h"

namespace plugin::states {

class SelectionState : public State {

public:
    void enter() override;
    void update() override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(Canvas *canvas) override;
    void draw() override;
    void exit() override;

private:
    void drawCursor();
    void drawPreview();
    int findSelectedNode(const glm::vec3 &position, const std::vector<NodePrimitive *> &nodes);
};

} // namespace plugin::states
