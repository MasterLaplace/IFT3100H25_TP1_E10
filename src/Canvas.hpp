#pragma once

/*
La classe Canvas g�re principalement l'arbre de structure.
L'arbre de structure est compos� de Node.
Chaque Node poss�de une Primitive2D ainsi qu'une liste de pointeurs vers d'autres Node qui sont ses enfants.
*/

#include "Node.hpp"
#include "ofMain.h"
#include <vector>

class Canvas {
public:
    std::vector<Node<Primitive2D> *> nodes;

    ~Canvas();

    static Canvas *getInstance();

    void addNode(Node<Primitive2D> *node);
    void removeNode(int id);

    void draw();
    Node<Primitive2D> *getChildById(const int id);
    void traverse();
    int findMouseSelectedNode(glm::vec2 point, std::vector<Node<Primitive2D> *> nodesToCheck);

private:
    void removeNodeRecursive(Node<Primitive2D> *node, Node<Primitive2D> *parent);
};
