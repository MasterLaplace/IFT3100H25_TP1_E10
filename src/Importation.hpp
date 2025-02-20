#pragma once

/*
Une classe pour pouvoir importer une image.
*/

#include "ofMain.h"

class Importation : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void importImage();

private:
    std::vector<ofImage> images;
    bool imageLoaded = false;
};