#include "Exporting.hpp"

namespace plugin::image {

void Exporting::setPixels()
{
    pixels.allocate(ofGetWidth(), ofGetHeight(), OF_PIXELS_RGB);
    glReadPixels(0, 0, ofGetWidth(), ofGetHeight(), GL_RGB, GL_UNSIGNED_BYTE, pixels.getData());
    std::cout << "Pixels allocated and read." << std::endl;
}

void Exporting::exportImage()
{
    ofImage image;
    image.setFromPixels(pixels);
    image.mirror(true, false);

    string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
    std::string filePath = "exported" + timestamp + ".png";
    if (image.save(filePath))
    {
        std::cout << "Image exported with timestamp: " << timestamp << std::endl;
    }
    else
    {
        std::cerr << "Failed to save image to " << filePath << std::endl;
    }
}

} // namespace plugin::image
