#pragma once

#include "State.hpp"

class DrawPointState : public State {
    void enter() override;
    void update() override;
    void draw() override;
    void exit() override;

private:
    void drawCursor();
    void drawPreview();
};
