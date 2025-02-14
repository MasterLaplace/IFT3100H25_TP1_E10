#include "Node2D.hpp"

// Le contructeur ne prend qu'un pointeur sur une Primitive2D.
Node2D::Node2D(Primitive2D *primitive) : primitive(primitive) {}

// Le destructeur s'assure de supprimer r�cursivement tout les enfants du Node2D.
Node2D::~Node2D()
{
    for (int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
}

// Permet d'ajouter un enfant � sa liste.
void Node2D::addChild(Node2D *child) { children.push_back(child); }

// Permet de dessiner sa propre Primitive2D ainsi que celle de tout ses enfants.
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

// Permet d'acc�der � une Node2D sp�cifique � l'aide de son identifiant unique.
Node2D *Node2D::getChildById(const int id)
{
    // Cas de base. Si on est sur la bonne Node2D on la retourne.
    if (primitive->id == id)
    {
        return this;
    }

    // Sinon on cherche de mani�re r�cursive dans ses enfants.
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

    // � d�finir en fonction du type d'information dont on a besoin pour afficher dans le UI.

};
