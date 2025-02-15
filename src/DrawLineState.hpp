#pragma once

#include "State.hpp"

class DrawLineState : public State {

public:
    void enter() override;
    void update() override;
    void draw() override;
    void exit() override;

private:
    void drawCursor();
    void drawPreview();
};
