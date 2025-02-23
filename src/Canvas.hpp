#pragma once

/*
La classe Canvas g�re principalement l'arbre de structure.
L'arbre de structure est compos� de Node2D.
Chaque Node2D poss�de une Primitive2D ainsi qu'une liste de pointeurs vers d'autres Node2D qui sont ses enfants.
*/

#include "Node2D.hpp"
#include "ofMain.h"
#include <vector>

class Canvas {
public:
    std::vector<Node2D *> nodes;

    ~Canvas();

    static Canvas *getInstance();

    void addNode(Node2D *node);
    void removeNode(int id);

    void draw();
    Node2D *getChildById(const int id);
    void traverse();

private:
    void removeNodeRecursive(Node2D *node, Node2D *parent);
};
