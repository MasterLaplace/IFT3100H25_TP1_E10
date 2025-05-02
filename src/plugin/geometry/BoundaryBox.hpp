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
    BoundaryBox(const BoundaryBox &other) = default;
    BoundaryBox(BoundaryBox &&other) = default;
    BoundaryBox &operator=(const BoundaryBox &other) = default;
    BoundaryBox &operator=(BoundaryBox &&other) = default;

    [[nodiscard]] inline bool operator==(const BoundaryBox &other) const noexcept
    {
        return _min == other._min && _max == other._max;
    }
    [[nodiscard]] inline bool operator!=(const BoundaryBox &other) const noexcept
    {
        return !(*this == other);
    }

    BoundaryBox(float x, float y, float z, float w, float h, float d) noexcept
    : _min(x, y, z), _max(x + w, y + h, z + d)
    {
        _min.x = std::min(_min.x, _max.x);
        _min.y = std::min(_min.y, _max.y);
        _min.z = std::min(_min.z, _max.z);
        _max.x = std::max(_min.x, _max.x);
        _max.y = std::max(_min.y, _max.y);
        _max.z = std::max(_min.z, _max.z);
    }

    BoundaryBox(const glm::vec3 &pos, const glm::vec3 &size) noexcept
        : _min(pos), _max(pos.x + size.x, pos.y + size.y, pos.z + size.z)
    {
        _min.x = std::min(_min.x, _max.x);
        _min.y = std::min(_min.y, _max.y);
        _min.z = std::min(_min.z, _max.z);
        _max.x = std::max(_min.x, _max.x);
        _max.y = std::max(_min.y, _max.y);
        _max.z = std::max(_min.z, _max.z);
    }

    ~BoundaryBox() = default;

    void load(const ofxAssimpMeshHelper &mesh);
    void load(const ofMesh &mesh);

    void setMin(const glm::vec3 &m);
    void setMax(const glm::vec3 &m);

    ofMesh getMesh() const;

    void draw() const;

    [[nodiscard]] inline bool contains(const glm::vec3 &point) const noexcept
    {
        return (point.x >= _min.x && point.x <= _max.x && point.y >= _min.y && point.y <= _max.y && point.z >= _min.z &&
                point.z <= _max.z);
    }
    [[nodiscard]] inline bool overlaps(const BoundaryBox &other) const noexcept
    {
        return (_min.x <= other._max.x && _max.x >= other._min.x && _min.y <= other._max.y && _max.y >= other._min.y &&
                _min.z <= other._max.z && _max.z >= other._min.z);
    }
    [[nodiscard]] inline bool contains(const BoundaryBox &other) const noexcept
    {
        return (_min.x <= other._min.x && _max.x >= other._max.x && _min.y <= other._min.y && _max.y >= other._max.y &&
                _min.z <= other._min.z && _max.z >= other._max.z);
    }

    [[nodiscard]] inline const glm::vec3 &getPosition() const noexcept { return _min; }
    [[nodiscard]] inline glm::vec3 getMin() const noexcept { return _min; }
    [[nodiscard]] inline glm::vec3 getMax() const noexcept { return _max; }
    [[nodiscard]] inline glm::vec3 getSize() const noexcept { return _max - _min; }
    [[nodiscard]] inline glm::vec3 getCenter() const noexcept { return (_min + _max) * 0.5f; }

    [[nodiscard]] inline float getWidth() const noexcept { return _max.x - _min.x; }
    [[nodiscard]] inline float getHeight() const noexcept { return _max.y - _min.y; }
    [[nodiscard]] inline float getDepth() const noexcept { return _max.z - _min.z; }

protected:
    glm::vec3 _min{0, 0, 0};
    glm::vec3 _max{1, 1, 1};
};

} // namespace plugin::geometry

#endif /* !BOUNDARYBOX_HPP_ */
