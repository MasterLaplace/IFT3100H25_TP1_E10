#pragma once

#include "Node2D.hpp"
#include "ofMain.h"
#include <vector>

class Canvas {
public:
    ~Canvas();
    void addNode(Node2D *node);
    void draw();
    Node2D *getChildById(const int id);
    void traverse();

private:
    std::vector<Node2D *> nodes;
};
