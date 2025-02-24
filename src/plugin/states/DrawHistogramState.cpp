#include "DrawHistogramState.hpp"

void plugin::states::DrawHistogramState::enter() 
{
    Canvas *canvas = Canvas::getInstance();

    ofImage canvasImage;
    canvasImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

    histogram.setup(canvasImage);
}

void plugin::states::DrawHistogramState::update() {}

void plugin::states::DrawHistogramState::draw() { histogram.draw();}

void plugin::states::DrawHistogramState::exit() {}

void plugin::states::DrawHistogramState::mousePressed(int x, int y, int button) {}

void plugin::states::DrawHistogramState::mouseReleased(int x, int y, int button) {}

void plugin::states::DrawHistogramState::setColor(int color) 
{ 
    this->color = color;
    histogram.setColor(color); 
}
