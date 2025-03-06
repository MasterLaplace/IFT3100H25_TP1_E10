/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Il est possible de dessiner des instances d’au moins 3 types de modèles 3D
** importés à partir d’un fichier externe.
*/

#ifndef OBJMODELS_HPP_
#define OBJMODELS_HPP_

#include "ofxAssimpModelLoader.h"

namespace plugin::geometry {

class ObjModel {
public:
    ObjModel() = default;
    ~ObjModel() = default;

    bool load(const std::string &path) { return yourModel.load(path); }

    void draw() { yourModel.draw(OF_MESH_FILL); }

    int getNumVertices() { return yourModel.getMesh(0).getNumVertices(); }

    int getNumFaces() { return yourModel.getMesh(0).getNumIndices() / 3; }

protected:
public:
    ofxAssimpModelLoader yourModel;
};

} // namespace plugin::geometry

#endif /* !OBJMODELS_HPP_ */
