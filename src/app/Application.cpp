#include "Application.hpp"

//--------------------------------------------------------------
void Application::setup()
{
    ofSetWindowTitle("IFT3100H25");

    ofLog() << "<app::setup>";

    currentController = &controller2D;
    currentController->setup();
}

//--------------------------------------------------------------
void Application::update() { currentController->update(); }

//--------------------------------------------------------------
void Application::draw() { currentController->draw(); }

//--------------------------------------------------------------
void Application::exit() { ofLog() << "<app::exit>"; }

//--------------------------------------------------------------
void Application::keyPressed(int key) { currentController->keyPressed(key); }

//--------------------------------------------------------------
void Application::keyReleased(int key) { ofLog() << "<app::keyReleased: " << key << ">"; }

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y)
{

    glm::vec2 position = glm::vec2(x, y);
    currentController->mouseMoved(position);
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
    ofLog() << "<app::mouse released at: (" << x << ", " << y << ")>";
}

//--------------------------------------------------------------
void Application::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void Application::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void Application::windowResized(int w, int h) {}

//--------------------------------------------------------------
void Application::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void Application::dragEvent(ofDragInfo dragInfo) {}
