#include "BoundaryBox.hpp"

namespace plugin::geometry {

BoundaryBox::BoundaryBox(const std::vector<glm::vec3> &points)
{
    if (points.empty())
    {
        min = glm::vec3(0.0f);
        max = glm::vec3(0.0f);
        return;
    }

    auto [minX, maxX] = std::minmax_element(points.begin(), points.end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.x < b.x; });
    auto [minY, maxY] = std::minmax_element(points.begin(), points.end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.y < b.y; });
    auto [minZ, maxZ] = std::minmax_element(points.begin(), points.end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.z < b.z; });

    min = glm::vec3(minX->x, minY->y, minZ->z);
    max = glm::vec3(maxX->x, maxY->y, maxZ->z);
}

glm::vec3 BoundaryBox::getMin() const { return min; }

glm::vec3 BoundaryBox::getMax() const { return max; }

} // namespace plugin::geometry
