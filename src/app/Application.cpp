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
void Application::keyPressed(int key) { }

//--------------------------------------------------------------
void Application::keyReleased(int key) {
    currentController->keyReleased(key);
    ofLog() << "<app::keyReleased: " << key << ">";
}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y)
{
    glm::vec2 position = glm::vec2(x, y);
    currentController->mouseMoved(position);
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button)
{
    glm::vec2 position = glm::vec2(x, y);
    currentController->mouseMoved(position);
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button)
{
    if (isInterceptedByImGui())
        return;

    currentController->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button)
{
    if (isInterceptedByImGui())
        return;

    currentController->mouseReleased(x, y, button);
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

bool Application::isInterceptedByImGui()
{
    // Interception de la sourie par ImGui si on est en train d'interagir avec l'interface.
    ImGuiIO &io = ImGui::GetIO();
    return io.WantCaptureMouse;
}
