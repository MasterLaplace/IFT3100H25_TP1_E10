#include "Application.hpp"

//--------------------------------------------------------------
void Application::setup()
{
    ofSetWindowTitle("IFT3100H25");

    ofLog() << "<app::setup>";

    // _image.load("test.png");
    // ofSetWindowShape(_image.getWidth(), _image.getHeight());
    // _histogram.setup(_image);
}

//--------------------------------------------------------------
void Application::update()
{
}

//--------------------------------------------------------------
void Application::draw()
{
    /*
    if (!_is_histogram_drawn)
    {
        _image.draw(0, 0);
    }

    else
    {
        _histogram.draw(_histogram_color);
    }
    */
}

//--------------------------------------------------------------
void Application::exit() { ofLog() << "<app::exit>"; }

//--------------------------------------------------------------
void Application::keyPressed(int key)
{
    /*
    if (key == ' ')
    {
        _is_histogram_drawn = false;
    }

    else if (key == 'r')
    {
        _is_histogram_drawn = true;
        _histogram_color = 'r';
    }

    else if (key == 'g')
    {
        _is_histogram_drawn = true;
        _histogram_color = 'g';
    }

    else if (key == 'b')
    {
        _is_histogram_drawn = true;
        _histogram_color = 'b';
    }
    */
}

//--------------------------------------------------------------
void Application::keyReleased(int key) { ofLog() << "<app::keyReleased: " << key << ">"; }

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y) {}

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
