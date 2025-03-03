#include "DrawHistogramState.hpp"

namespace plugin::states {

void DrawHistogramState::enter()
{
    // Canvas *canvas = Canvas::getInstance();

    ofImage canvasImage;
    canvasImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

    histogram.setup(canvasImage);
}

void DrawHistogramState::update() {}

void DrawHistogramState::draw() { histogram.draw(); }

void DrawHistogramState::exit() {}

void DrawHistogramState::mousePressed(int x, int y, int button) {}

void DrawHistogramState::mouseReleased(int x, int y, int button) {}

void DrawHistogramState::setColor(int color)
{
    this->color = color;
    histogram.setColor(color);
}

} // namespace plugin::states
