#pragma once

#include "Primitive2D.hpp"
#include <vector>

class Node2D {
public:
    Primitive2D *primitive;

    Node2D(Primitive2D *primitive);
    ~Node2D();

    void addChild(Node2D *child);
    void draw();
    Node2D *getChildById(const int id);
    void traverse();

private:
    std::vector<Node2D*> children;
};
