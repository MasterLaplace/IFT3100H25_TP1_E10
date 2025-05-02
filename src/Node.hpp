/*
La classe Node sert à peupler l'arbre pour le graphe de scene.
Cette structure de données est gérée par la classe Canvas.
Chaque Node contient une Primitive et une liste de pointeurs sur des Node qui sont ses enfants.
*/

#ifndef NODE_HPP_
#define NODE_HPP_

#include "plugin/primitive/primitives.hpp"
#include <memory>
#include <queue>
#include <vector>

template <typename T> class Node {
public:
    /**
     * @brief Construit un nouveau Node avec une Primitive.
     *
     * @param primitive  Un pointeur sur une Primitive.
     */
    Node(const std::shared_ptr<T> &primitive, const std::string &name);

    /**
     * @brief Le destructeur s'assure de supprimer récursivement tout les enfants du Node.
     */
    ~Node();

    /**
     * @brief Ajoute un enfant  à sa liste.
     *
     * @param child  Un pointeur sur un Node.
     */
    void addChild(Node<T> *child);

    /**
     * @brief Dessine la Primitive du Node et celle de tout ses enfants
     *
     */
    void draw();

    /**
     * @brief Acc�der à une Node spécifique à l'aide de son identifiant unique.
     *
     * @param id  L'identifiant unique de la Primitive.
     * @return Node<T>*  Un pointeur sur la Node correspondante.
     */
    [[nodiscard]] Node<T> *getChildById(const uint32_t id);

    /**
     * @brief Parcours l'arbre en affichant l'identifiant de chaque Primitive.
     *
     */
    void traverse();

    size_t size() const
    {
        if (_primitive == nullptr)
            return 0;

        size_t size = 1;

        for (auto &child : _children)
            size += child->size();

        return size;
    }

    void getPrimitives(std::vector<std::shared_ptr<T>> &list) const
    {
        if (_primitive == nullptr)
            return;

        list.emplace_back(_primitive->clone());

        for (auto &child : _children)
            child->getPrimitives(list);
    }

    [[nodiscard]] inline std::shared_ptr<T> &getPrimitive() { return _primitive; }
    [[nodiscard]] inline const uint32_t getId() const { return _id; }
    [[nodiscard]] inline const std::string &getName() const { return _name; }
    [[nodiscard]] inline std::vector<Node<T> *> &getChildren() { return _children; }

private:
    std::shared_ptr<T> _primitive;
    uint32_t _id = 0;
    std::string _name{};
    std::vector<Node<T> *> _children;

    inline static uint32_t _nextId = 0;
};

#include "Node.inl"

using NodePrimitive = Node<plugin::primitive::Primitive>;

#endif /* !NODE_HPP_ */
