#include "Node.hpp"

template <typename T> Node<T>::Node(const std::shared_ptr<T> &primitive, const std::string &name) : _primitive(primitive), _name(name)
{
    _id = _nextId++;
    _name += " " + std::to_string(_id);
}

template <typename T> Node<T>::~Node()
{
    for (size_t i = 0; i < _children.size(); i++)
    {
        delete _children[i];
    }
    _children.clear();
    _primitive.reset();
    _primitive = nullptr;
    _children.shrink_to_fit();
    _children.clear();
    _name.clear();
    _id = 0;
}

template <typename T> void Node<T>::addChild(Node<T> *child) { _children.push_back(child); }

template <typename T> void Node<T>::draw()
{
    if (_primitive)
    {
        _primitive->draw();
    }

    for (size_t i = 0; i < _children.size(); i++)
    {
        _children[i]->draw();
    }
}

template <typename T> Node<T> *Node<T>::getChildById(const uint32_t id)
{
    // Cas de base. Si on est sur la bonne Node on la retourne.
    if (_id == id)
    {
        return this;
    }

    // Sinon on cherche de manière récursive dans ses enfants.
    for (auto &child : _children)
    {
        if (auto result = child->getChildById(id))
        {
            return result; // Si on trouve quelque chose on le retourne.
        }
    }
    return nullptr; // Sinon, on retourne un nullptr.
}

template <typename T> void Node<T>::traverse()
{

    if (_primitive != nullptr)
    {
        std::cout << "Name: " << _name << std::endl;
    }

    for (size_t i = 0; i < _children.size(); i++)
    {
        _children[i]->traverse();
    }
};
