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

void Canvas::removeNode(int id)
{
    Node2D *node = getChildById(id);
    if (node)
    {
        // La boucle qui permet de deleter les enfants de la node.
        for (int i = 0; i < node->children.size(); i++)
        {
            removeNode(node->children[i]->primitive->id);
        }

        // On cherche la node à supprimer dans la liste de nodes.
        // Si on la trouve, on la supprime.
        // Sinon, on appelle la fonction removeNodeRecursive sur tous.
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            if (*it == node)
            {
                delete *it;
                nodes.erase(it);
                return;
            }
        }

        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            removeNodeRecursive(node, *it);
        }
    }
}

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

void Canvas::removeNodeRecursive(Node2D *node, Node2D *parent)
{
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it)
    {
        if (*it == node)
        {
            for (int i = 0; i < node->children.size(); i++)
            {
                removeNode(node->children[i]->primitive->id);
            }

            delete *it;
            parent->children.erase(it);
            return;
        }
        else
        {
            removeNodeRecursive(node, *it);
        }
    }
}
