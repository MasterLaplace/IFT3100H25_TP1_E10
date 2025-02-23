#pragma once

/*
La classe Node2D sert � peupler l'arbre pour le graphe de scene.
Cette structure de donn�es est g�r�e par la classe Canvas.
Chaque Node2D contient une Primitive2D et une liste de pointeurs sur des Node2D qui sont ses enfants.
*/

#include "plugin/primitive/primitive.hpp"
#include <vector>

using namespace plugin::primitive;

class Node2D {
public:
    Primitive2D *primitive;
    std::vector<Node2D *> children;

    Node2D(Primitive2D *primitive);
    ~Node2D();

    void addChild(Node2D *child);
    void draw();
    Node2D *getChildById(const int id);
    void traverse();

private:
};
