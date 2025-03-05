#pragma once

#include "ofMain.h"

class Camera : public ofCamera {
public:
    Camera();

    void toggleProjection();
    void update();
    
private:
    bool isOrthographic = false;
};
