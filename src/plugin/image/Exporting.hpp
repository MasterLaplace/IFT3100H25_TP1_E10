#pragma once

#include "ofMain.h"

namespace plugin::image {

class Exporting {
public:
    void setPixels();
    void exportImage();
    
private:
    ofPixels pixels;
    
};

} // namespace plugin::image

