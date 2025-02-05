#pragma once

#include "ofMain.h"
#include "Primitive2D.h"
#include <vector>

class Canvas {
public:
    void addPrimitive(Primitive2D* primitive);

private:

    std::vector<Primitive2D*> shapes;

    void drawPoint();
};
