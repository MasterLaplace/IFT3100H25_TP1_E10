#include "Canvas.hpp"

// M�thode statique pour obtenir l'instance du Canvas.
Canvas *Canvas::getInstance()
{
    static Canvas instance;
    return &instance;
}

// � la destruction du Canvas, on s'assure qu'on d�truit l'arbre de Node.
Canvas::~Canvas()
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

// Pour ajouter un enfant � sa liste de Node.
void Canvas::addNode(Node<Primitive2D> *node) { nodes.push_back(node); }

void Canvas::removeNode(int id)
{
    Node<Primitive2D> *node = getChildById(id);
    if (node)
    {
        // La boucle qui permet de deleter les enfants de la node.
        for (size_t i = 0; i < node->children.size(); i++)
        {
            removeNode(node->children[i]->primitive->id);
        }

        // On cherche la node � supprimer dans la liste de nodes.
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

// Pour dessiner � l'�cran toutes les Primitive2D qui sont contenu dans chaques noeuds de l'arbre.
void Canvas::draw()
{
    ofBackground(255);

    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }
}

// Pour r�cup�rer un noeud sp�cifique � l'aide de son identifiant unique.
Node<Primitive2D> *Canvas::getChildById(const int id)
{
    Node<Primitive2D> *result = nullptr;

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
    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodes[i]->traverse();
    }
}

void Canvas::removeNodeRecursive(Node<Primitive2D> *node, Node<Primitive2D> *parent)
{
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it)
    {
        if (*it == node)
        {
            for (size_t i = 0; i < node->children.size(); i++)
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

int Canvas::findMouseSelectedNode(glm::vec2 point, std::vector<Node<Primitive2D> *> nodesToCheck)
{
    for (int i = nodesToCheck.size() - 1; i >= 0; i--)
    {
        int nodeId = findMouseSelectedNode(point, nodesToCheck[i]->children);

        if (nodeId != -1)
        {
            return nodeId;
        }

        if (nodes[i]->primitive->isInside(&point))
        {
            return nodesToCheck[i]->primitive->id;
        }
    }

    return -1; // Retourne -1 si rien n'est trouv�
}
