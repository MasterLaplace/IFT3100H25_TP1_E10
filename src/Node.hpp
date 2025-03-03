#pragma once

/*
La classe Node sert à peupler l'arbre pour le graphe de scene.
Cette structure de données est gérée par la classe Canvas.
Chaque Node contient une Primitive2D et une liste de pointeurs sur des Node qui sont ses enfants.
*/

#include "plugin/primitive/primitive.hpp"
#include <vector>

using namespace plugin::primitive;

template <typename T>
class Node {
public:
    /**
     * @brief Construit un nouveau Node avec une Primitive2D.
     *
     * @param primitive  Un pointeur sur une Primitive2D.
     */
    Node(T *primitive);

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
     * @brief Dessine la Primitive2D du Node et celle de tout ses enfants
     *
     */
    void draw();

    /**
     * @brief Acc�der à une Node spécifique à l'aide de son identifiant unique.
     *
     * @param id  L'identifiant unique de la Primitive2D.
     * @return Node<T>*  Un pointeur sur la Node correspondante.
     */
    Node<T> *getChildById(const int id);

    /**
     * @brief Parcours l'arbre en affichant l'identifiant de chaque Primitive2D.
     *
     */
    void traverse();

public:
    T *primitive;
    std::vector<Node<T> *> children;
};

#include "Node.inl"
