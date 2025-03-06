#include "Exporting.hpp"

namespace plugin::image {

void Exporting::setPixels()
{
    pixels.allocate(ofGetWidth(), ofGetHeight(), OF_PIXELS_RGB);
    glReadPixels(0, 0, ofGetWidth(), ofGetHeight(), GL_RGB, GL_UNSIGNED_BYTE, pixels.getData());
}

void Exporting::exportImage()
{
    ofImage image;
    image.setFromPixels(pixels);
    image.mirror(true, false);

    string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
    std::string filePath = "exported" + timestamp + ".png";

    auto result = ofSystemSaveDialog(filePath, "Enregistrer sous...");
    if (result.bSuccess)
    {
        if (image.save(result.filePath))
        {
            std::cout << "Image exported with timestamp: " << timestamp << std::endl;
        }
        else
        {
            ofSystemAlertDialog("Erreur lors de l'exportation de l'image.");
        }
    }
}

} // namespace plugin::image
