#pragma once

#include "ofMain.h"

class Camera : public ofCamera {
public:
    bool isOrthographic = false;
    Camera();

    void toggleProjection();
    void update();

private:

};
