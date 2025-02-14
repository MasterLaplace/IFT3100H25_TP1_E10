#include "Canvas.hpp"

Canvas::~Canvas()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

void Canvas::addNode(Node2D *node) {

    nodes.push_back(node);

}

void Canvas::draw() {

    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }

}

Node2D *Canvas::getChildById(const int id)
{
    Node2D *result = nullptr;

    //On appelle la fonction getChildById sur tous les enfants de la racine.
    for (auto node : nodes)
    {
        result = node->getChildById(id);
    }

    return result;
}

void Canvas::traverse() {

    //À définir en fonction du type d'information dont on a besoin pour afficher dans le UI.

}
