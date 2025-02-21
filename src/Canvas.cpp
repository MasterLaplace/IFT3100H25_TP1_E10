#include "Canvas.hpp"

// Méthode statique pour obtenir l'instance du Canvas.
Canvas *Canvas::getInstance()
{
    static Canvas instance;
    return &instance;
}

// À la destruction du Canvas, on s'assure qu'on détruit l'arbre de Node2D.
Canvas::~Canvas()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

// Pour ajouter un enfant à sa liste de Node2D.
void Canvas::addNode(Node2D *node) { nodes.push_back(node); }

// Pour dessiner à l'écran toutes les Primitive2D qui sont contenu dans chaques noeuds de l'arbre.
void Canvas::draw()
{
    ofBackground(255);

    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }
}

// Pour récupérer un noeud spécifique à l'aide de son identifiant unique.
Node2D *Canvas::getChildById(const int id)
{
    Node2D *result = nullptr;

    // On appelle la fonction getChildById sur tous les enfants de la racine.
    for (auto node : nodes)
    {
        if (result == nullptr)
        {
            result = node->getChildById(id);
        }
    }

    return result;
}

void Canvas::traverse()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->traverse();
    }
}
