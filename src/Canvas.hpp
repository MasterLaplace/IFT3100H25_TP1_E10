#pragma once

/*
La classe Canvas g�re principalement l'arbre de structure.
L'arbre de structure est compos� de Node.
Chaque Node poss�de une Primitive ainsi qu'une liste de pointeurs vers d'autres Node qui sont ses enfants.
*/

#include "Node.hpp"
#include "ofMain.h"
#include <vector>

class Canvas {
public:
    std::vector<NodePrimitive *> nodes;
    ofColor backgroundColor;

    Canvas();
    ~Canvas();

    static Canvas *getInstance();

    void setBackgroundColor(const ofColor &color);

    void addNode(NodePrimitive *node);
    void removeNode(const uint32_t id);

    void draw();
    NodePrimitive *getChildById(const uint32_t id);
    void traverse();
    int findMouseSelectedNode(const glm::vec3 &point, std::vector<NodePrimitive *> &nodesToCheck);

    std::vector<std::shared_ptr<plugin::primitive::Primitive>> getPrimitives() const;

private:
    void removeNodeRecursive(NodePrimitive *node, NodePrimitive *parent);
};
#pragma once
