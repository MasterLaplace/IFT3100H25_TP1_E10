#include "Canvas.hpp"

//� la destruction du Canvas, on s'assure qu'on d�truit l'arbre de Node2D.
Canvas::~Canvas()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

//Pour ajouter un enfant � sa liste de Node2D.
void Canvas::addNode(Node2D *node) { nodes.push_back(node); }

//Pour dessiner � l'�cran toutes les Primitive2D qui sont contenu dans chaques noeuds de l'arbre.
void Canvas::draw()
{

    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }
}

//Pour r�cup�rer un noeud sp�cifique � l'aide de son identifiant unique.
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

    // � d�finir en fonction du type d'information dont on a besoin pour afficher dans le UI.
}
