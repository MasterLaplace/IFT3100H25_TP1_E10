#pragma once

#include "Primitive2D.h"
#include "ofMain.h"
#include <vector>

class Canvas {
public:
    void addPrimitive(Primitive2D *primitive);

private:
    std::vector<Primitive2D *> shapes;

    void drawPoint();
};
