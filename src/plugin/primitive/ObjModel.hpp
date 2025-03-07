/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Il est possible de dessiner des instances d’au moins 3 types de modèles 3D
** importés à partir d’un fichier externe.
*/

#ifndef OBJMODEL_HPP_
#define OBJMODEL_HPP_

#include "../geometry/BoundaryBox.hpp"
#include "Primitive.hpp"
#include "ofxAssimpModelLoader.h"

namespace plugin::primitive {

class Model : public ofxAssimpModelLoader {
public:
    Model() = default;
    Model(const Model &other) { *this = other; }
    ~Model() = default;

    // ajoute un operator= pour pouvoir copier le model
    Model &operator=(const Model &other)
    {
        if (this != &other)
        {
            file = other.file;
            scene_min = other.scene_min;
            scene_max = other.scene_max;
            scene_center = other.scene_center;
            normalizeScale = other.normalizeScale;
            normalizedScale = other.normalizedScale;
            rotAngle = other.rotAngle;
            rotAxis = other.rotAxis;
            scale = other.scale;
            pos = other.pos;
            modelMatrix = other.modelMatrix;
            textures = other.textures;
            modelMeshes = other.modelMeshes;
            animations = other.animations;
            currentAnimation = other.currentAnimation;
            mCullType = other.mCullType;
            bUsingTextures = other.bUsingTextures;
            bUsingNormals = other.bUsingNormals;
            bUsingColors = other.bUsingColors;
            bUsingMaterials = other.bUsingMaterials;
            normalizeFactor = other.normalizeFactor;
            scene = other.scene;
            store = other.store;
        }
        return *this;
    }
};

class ObjModel : public Primitive {
public:
    ObjModel(PrimitiveParams params);
    ObjModel(PrimitiveParams params, const std::shared_ptr<plugin::primitive::ObjModel> &other);
    // ObjModel(const ObjModel &other);
    ~ObjModel() override = default;

    bool load(const std::string &path);

    void draw() override;

    bool isInside(const glm::vec3 &point) override;

    [[nodiscard]] int getNumVertices();

    [[nodiscard]] int getNumFaces();

    [[nodiscard]] Model getModel() { return yourModel; }

protected:
public:
    Model yourModel;
    geometry::BoundaryBox bbox;
};

} // namespace plugin::primitive

#endif /* !OBJMODEL_HPP_ */
