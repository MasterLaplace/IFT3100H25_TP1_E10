#include "Canvas.hpp"

// Méthode statique pour obtenir l'instance du Canvas.
Canvas *Canvas::getInstance()
{
    static Canvas instance;
    return &instance;
}

void Canvas::setBackgroundColor(const ofColor &color) { backgroundColor = color; }

Canvas::Canvas() : backgroundColor(ofColor(40)) {}

// A la destruction du Canvas, on s'assure qu'on d�truit l'arbre de Node.
Canvas::~Canvas()
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

// Pour ajouter un enfant à sa liste de Node.
void Canvas::addNode(NodePrimitive *node) { nodes.push_back(node); }

void Canvas::removeNode(const uint32_t id)
{
    NodePrimitive *node = getChildById(id);

    if (!node)
        return;

    // La boucle qui permet de supprimer les enfants de la node.
    for (size_t i = 0; i < node->getChildren().size(); i++)
    {
        removeNode(node->getChildren()[i]->getId());
    }

    // On cherche la node à supprimer dans la liste de nodes.
    // Si on la trouve, on la supprime.
    // Sinon, on appelle la fonction removeNodeRecursive sur tous.
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (*it == node)
        {
            nodes.erase(it);
            return;
        }
    }

    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        removeNodeRecursive(node, *it);
    }
}

// Pour dessiner à l'écran toutes les Primitive qui sont contenu dans chaques noeuds de l'arbre.
void Canvas::draw()
{
    ofBackground(backgroundColor);

    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodes[i]->draw();
    }
}

// Pour récupérer un noeud spécifique à l'aide de son identifiant unique.
NodePrimitive *Canvas::getChildById(const uint32_t id)
{
    NodePrimitive *result = nullptr;

    // On appelle la fonction getChildById sur tous les enfants de la racine.
    for (auto &node : nodes)
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

void Canvas::removeNodeRecursive(NodePrimitive *node, NodePrimitive *parent)
{
    auto &children = parent->getChildren();

    for (auto it = children.begin(); it != children.end(); ++it)
    {
        if (*it == node)
        {
            for (size_t i = 0; i < node->getChildren().size(); i++)
            {
                removeNode(node->getChildren()[i]->getId());
            }

            children.erase(it);
            return;
        }
        else
        {
            removeNodeRecursive(node, *it);
        }
    }
}

int Canvas::findMouseSelectedNode(const glm::vec3 &point, std::vector<NodePrimitive *> &nodesToCheck)
{
    for (int i = nodesToCheck.size() - 1; i >= 0; i--)
    {
        int nodeId = findMouseSelectedNode(point, nodesToCheck[i]->getChildren());

        if (nodeId != -1)
        {
            return nodeId;
        }

        if (nodes[i]->getPrimitive()->isInside(point))
        {
            return nodesToCheck[i]->getId();
        }
    }

    return -1; // Retourne -1 si rien n'est trouvé
}
