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

class ObjModels {
public:
    ObjModels() = default;
    ~ObjModels() = default;

    bool load(const std::string &path) { return yourModel.load(path); }

    void draw() { yourModel.draw(OF_MESH_FILL); }

protected:
public:
    ofxAssimpModelLoader yourModel;
};

} // namespace plugin::geometry

#endif /* !OBJMODELS_HPP_ */
