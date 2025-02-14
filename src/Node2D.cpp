#include "Node2D.hpp"

Node2D::Node2D(Primitive2D *primitive) : primitive(primitive) {}

Node2D::~Node2D()
{
    for (int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
}

void Node2D::addChild(Node2D *child) { children.push_back(child); }

void Node2D::draw()
{

    if (primitive)
    {
        primitive->draw();
    }

    for (int i = 0; i < children.size(); i++)
    {
        children[i]->draw();
    }
}

Node2D *Node2D::getChildById(const int id)
{
    // Cas de base. Si on est sur la bonne Node2D on la retourne.
    if (primitive->id == id)
    {
        return this;
    }

    // Sinon on cherche de manière récursive dans ses enfants.
    for (auto child : children)
    {
        Node2D *result = child->getChildById(id);
        if (result)
        {
            return result; // Si on trouve quelque chose on le retourne.
        }
    }
    return nullptr; // Sinon, on retourne un nullptr.
}

void Node2D::traverse() {

    // À définir en fonction du type d'information dont on a besoin pour afficher dans le UI.

};
