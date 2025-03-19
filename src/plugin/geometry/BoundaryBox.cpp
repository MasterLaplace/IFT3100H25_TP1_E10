#include "BoundaryBox.hpp"
#include "ofMain.h"

namespace plugin::geometry {

void BoundaryBox::load(const ofxAssimpMeshHelper &mesh)
{
    if (mesh.mesh->mNumVertices == 0)
    {
        min = glm::vec3(0.0f);
        max = glm::vec3(0.0f);
        return;
    }

    min = glm::vec3(1e10f);
    max = glm::vec3(-1e10f);

    for (unsigned int i = 0; i < mesh.mesh->mNumVertices; ++i)
    {
        auto vertex = mesh.mesh->mVertices[i];
        auto transformed = mesh.matrix * glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f);

        min.x = std::min(min.x, transformed.x);
        min.y = std::min(min.y, transformed.y);
        min.z = std::min(min.z, transformed.z);

        max.x = std::max(max.x, transformed.x);
        max.y = std::max(max.y, transformed.y);
        max.z = std::max(max.z, transformed.z);
    }
}

void BoundaryBox::load(const ofMesh &mesh)
{
    if (mesh.getNumVertices() == 0)
    {
        min = glm::vec3(0.0f);
        max = glm::vec3(0.0f);
        return;
    }

    auto [minX, maxX] = std::minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.x < b.x; });
    auto [minY, maxY] = std::minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.y < b.y; });
    auto [minZ, maxZ] = std::minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.z < b.z; });

    min = glm::vec3(minX->x, minY->y, minZ->z);
    max = glm::vec3(maxX->x, maxY->y, maxZ->z);
}

glm::vec3 BoundaryBox::getMin() const { return min; }

glm::vec3 BoundaryBox::getMax() const { return max; }

void BoundaryBox::setMin(const glm::vec3 &m) { min = m; }

void BoundaryBox::setMax(const glm::vec3 &m) { max = m; }

ofMesh BoundaryBox::getMesh() const
{
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_LINES);

    // face avant
    mesh.addVertex(glm::vec3(min.x, min.y, min.z));
    mesh.addVertex(glm::vec3(max.x, min.y, min.z));
    mesh.addVertex(glm::vec3(max.x, min.y, min.z));
    mesh.addVertex(glm::vec3(max.x, max.y, min.z));
    mesh.addVertex(glm::vec3(max.x, max.y, min.z));
    mesh.addVertex(glm::vec3(min.x, max.y, min.z));
    mesh.addVertex(glm::vec3(min.x, max.y, min.z));
    mesh.addVertex(glm::vec3(min.x, min.y, min.z));

    // face arrière
    mesh.addVertex(glm::vec3(min.x, min.y, max.z));
    mesh.addVertex(glm::vec3(max.x, min.y, max.z));
    mesh.addVertex(glm::vec3(max.x, min.y, max.z));
    mesh.addVertex(glm::vec3(max.x, max.y, max.z));
    mesh.addVertex(glm::vec3(max.x, max.y, max.z));
    mesh.addVertex(glm::vec3(min.x, max.y, max.z));
    mesh.addVertex(glm::vec3(min.x, max.y, max.z));
    mesh.addVertex(glm::vec3(min.x, min.y, max.z));

    // arêtes
    mesh.addVertex(glm::vec3(min.x, min.y, min.z));
    mesh.addVertex(glm::vec3(min.x, min.y, max.z));
    mesh.addVertex(glm::vec3(max.x, min.y, min.z));
    mesh.addVertex(glm::vec3(max.x, min.y, max.z));
    mesh.addVertex(glm::vec3(max.x, max.y, min.z));
    mesh.addVertex(glm::vec3(max.x, max.y, max.z));
    mesh.addVertex(glm::vec3(min.x, max.y, min.z));
    mesh.addVertex(glm::vec3(min.x, max.y, max.z));

    return mesh;
}

void BoundaryBox::draw() const
{
    ofSetColor(ofColor::green);
    ofSetLineWidth(1);
    ofNoFill();

    // face avant
    ofDrawLine(min.x, min.y, min.z, max.x, min.y, min.z);
    ofDrawLine(max.x, min.y, min.z, max.x, max.y, min.z);
    ofDrawLine(max.x, max.y, min.z, min.x, max.y, min.z);
    ofDrawLine(min.x, max.y, min.z, min.x, min.y, min.z);

    // face arrière
    ofDrawLine(min.x, min.y, max.z, max.x, min.y, max.z);
    ofDrawLine(max.x, min.y, max.z, max.x, max.y, max.z);
    ofDrawLine(max.x, max.y, max.z, min.x, max.y, max.z);
    ofDrawLine(min.x, max.y, max.z, min.x, min.y, max.z);

    // arêtes
    ofDrawLine(min.x, min.y, min.z, min.x, min.y, max.z);
    ofDrawLine(max.x, min.y, min.z, max.x, min.y, max.z);
    ofDrawLine(max.x, max.y, min.z, max.x, max.y, max.z);
    ofDrawLine(min.x, max.y, min.z, min.x, max.y, max.z);

    // diagonales
    ofDrawLine(min.x, min.y, min.z, max.x, max.y, max.z);
    ofDrawLine(max.x, min.y, min.z, min.x, max.y, max.z);
    ofDrawLine(min.x, min.y, max.z, max.x, max.y, min.z);
    ofDrawLine(max.x, min.y, max.z, min.x, max.y, min.z);

    // dessiner les sommets
    ofSetColor(ofColor::red);
    ofDrawSphere(min.x, min.y, min.z, 2.0f);
    ofDrawSphere(max.x, min.y, min.z, 2.0f);
    ofDrawSphere(max.x, max.y, min.z, 2.0f);
    ofDrawSphere(min.x, max.y, min.z, 2.0f);
    ofDrawSphere(min.x, min.y, max.z, 2.0f);
    ofDrawSphere(max.x, min.y, max.z, 2.0f);
    ofDrawSphere(max.x, max.y, max.z, 2.0f);
    ofDrawSphere(min.x, max.y, max.z, 2.0f);
}

} // namespace plugin::geometry
