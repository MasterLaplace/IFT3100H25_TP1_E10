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
    void mouseReleased(int x, int y, int button) override;
    void draw() override;
    void exit() override;

private:
    void drawCursor();
    void drawPreview();
    int  findSelectedNode(glm::vec2 position, std::vector<Node2D *> nodes);
};

} // namespace plugin::states

