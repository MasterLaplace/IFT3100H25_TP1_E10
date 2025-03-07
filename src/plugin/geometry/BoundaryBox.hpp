/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Une option permet de dessiner les arêtes d’une boîte d’une taille juste assez
** grande pour envelopper tous les sommets d’un modèle 3D pour chaque type
** de modèle qu’il est possible d’utiliser avec l’application.
*/

#ifndef BOUNDARYBOX_HPP_
#define BOUNDARYBOX_HPP_

#include <algorithm>
#include <glm/glm.hpp>
#include <vector>

#include "ofxAssimpModelLoader.h"

namespace plugin::geometry {

class BoundaryBox {
public:
    BoundaryBox() = default;
    ~BoundaryBox() = default;

    void load(const ofxAssimpMeshHelper &mesh);
    void load(const ofMesh &mesh);

    [[nodiscard]] glm::vec3 getMin() const;
    [[nodiscard]] glm::vec3 getMax() const;

    void draw() const;

private:
    glm::vec3 min;
    glm::vec3 max;
};

} // namespace plugin::geometry

#endif /* !BOUNDARYBOX_HPP_ */
