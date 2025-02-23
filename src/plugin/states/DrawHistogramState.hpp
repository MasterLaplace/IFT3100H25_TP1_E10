#pragma once

#include "Canvas.hpp"
#include "State.hpp"
#include "plugin/image/Histogram.hpp"

namespace plugin::states {

class DrawHistogramState : public State {

public:
    void enter() override;
    void update() override;
    void draw() override;
    void exit() override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;


private:
    plugin::image::Histogram histogram;
};

} // namespace plugin::states
