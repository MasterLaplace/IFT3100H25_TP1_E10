#include "Node.hpp"

template <typename T>
Node<T>::Node(T *primitive) : primitive(primitive) {}

template <typename T>
Node<T>::~Node()
{
    for (int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
    delete primitive;
}

template <typename T>
void Node<T>::addChild(Node<T> *child) { children.push_back(child); }

template <typename T>
void Node<T>::draw()
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

template <typename T>
Node<T> *Node<T>::getChildById(const int id)
{
    // Cas de base. Si on est sur la bonne Node on la retourne.
    if (primitive->id == id)
    {
        return this;
    }

    // Sinon on cherche de mani�re r�cursive dans ses enfants.
    for (auto child : children)
    {
        Node<T> *result = child->getChildById(id);
        if (result)
        {
            return result; // Si on trouve quelque chose on le retourne.
        }
    }
    return nullptr; // Sinon, on retourne un nullptr.
}

template <typename T>
void Node<T>::traverse()
{

    if (primitive != nullptr)
    {
        std::cout << "Primitive: " << primitive->id << std::endl;
    }

    for (int i = 0; i < children.size(); i++)
    {
        children[i]->traverse();
    }
};
