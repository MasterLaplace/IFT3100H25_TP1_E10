#include "Canvas.hpp"

//À la destruction du Canvas, on s'assure qu'on détruit l'arbre de Node2D.
Canvas::~Canvas()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

//Pour ajouter un enfant à sa liste de Node2D.
void Canvas::addNode(Node2D *node) { nodes.push_back(node); }

//Pour dessiner à l'écran toutes les Primitive2D qui sont contenu dans chaques noeuds de l'arbre.
void Canvas::draw()
{

    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }
}

//Pour récupérer un noeud spécifique à l'aide de son identifiant unique.
Node2D *Canvas::getChildById(const int id)
{
    Node2D *result = nullptr;

    // On appelle la fonction getChildById sur tous les enfants de la racine.
    for (auto node : nodes)
    {
        result = node->getChildById(id);
    }

    return result;
}

void Canvas::traverse()
{

    // À définir en fonction du type d'information dont on a besoin pour afficher dans le UI.
}
