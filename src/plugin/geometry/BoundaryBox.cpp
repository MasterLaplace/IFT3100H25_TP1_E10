#include "BoundaryBox.hpp"
#include "ofMain.h"

namespace plugin::geometry {

void BoundaryBox::load(const ofxAssimpMeshHelper &mesh)
{
    if (mesh.mesh->mNumVertices == 0)
    {
        _min = glm::vec3(0.0f);
        _max = glm::vec3(0.0f);
        return;
    }

    _min = glm::vec3(1e10f);
    _max = glm::vec3(-1e10f);

    for (unsigned int i = 0; i < mesh.mesh->mNumVertices; ++i)
    {
        auto vertex = mesh.mesh->mVertices[i];
        auto transformed = mesh.matrix * glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f);

        _min.x = std::min(_min.x, transformed.x);
        _min.y = std::min(_min.y, transformed.y);
        _min.z = std::min(_min.z, transformed.z);

        _max.x = std::max(_max.x, transformed.x);
        _max.y = std::max(_max.y, transformed.y);
        _max.z = std::max(_max.z, transformed.z);
    }
}

void BoundaryBox::load(const ofMesh &mesh)
{
    if (mesh.getNumVertices() == 0)
    {
        _min = glm::vec3(0.0f);
        _max = glm::vec3(0.0f);
        return;
    }

    auto [minX, maxX] = std::minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.x < b.x; });
    auto [minY, maxY] = std::minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.y < b.y; });
    auto [minZ, maxZ] = std::minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
                                            [](const glm::vec3 &a, const glm::vec3 &b) { return a.z < b.z; });

    _min = glm::vec3(minX->x, minY->y, minZ->z);
    _max = glm::vec3(maxX->x, maxY->y, maxZ->z);
}

void BoundaryBox::setMin(const glm::vec3 &m) { _min = m; }

void BoundaryBox::setMax(const glm::vec3 &m) { _max = m; }

ofMesh BoundaryBox::getMesh() const
{
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_LINES);

    // face avant
    mesh.addVertex(glm::vec3(_min.x, _min.y, _min.z));
    mesh.addVertex(glm::vec3(_max.x, _min.y, _min.z));
    mesh.addVertex(glm::vec3(_max.x, _min.y, _min.z));
    mesh.addVertex(glm::vec3(_max.x, _max.y, _min.z));
    mesh.addVertex(glm::vec3(_max.x, _max.y, _min.z));
    mesh.addVertex(glm::vec3(_min.x, _max.y, _min.z));
    mesh.addVertex(glm::vec3(_min.x, _max.y, _min.z));
    mesh.addVertex(glm::vec3(_min.x, _min.y, _min.z));

    // face arrière
    mesh.addVertex(glm::vec3(_min.x, _min.y, _max.z));
    mesh.addVertex(glm::vec3(_max.x, _min.y, _max.z));
    mesh.addVertex(glm::vec3(_max.x, _min.y, _max.z));
    mesh.addVertex(glm::vec3(_max.x, _max.y, _max.z));
    mesh.addVertex(glm::vec3(_max.x, _max.y, _max.z));
    mesh.addVertex(glm::vec3(_min.x, _max.y, _max.z));
    mesh.addVertex(glm::vec3(_min.x, _max.y, _max.z));
    mesh.addVertex(glm::vec3(_min.x, _min.y, _max.z));

    // arêtes
    mesh.addVertex(glm::vec3(_min.x, _min.y, _min.z));
    mesh.addVertex(glm::vec3(_min.x, _min.y, _max.z));
    mesh.addVertex(glm::vec3(_max.x, _min.y, _min.z));
    mesh.addVertex(glm::vec3(_max.x, _min.y, _max.z));
    mesh.addVertex(glm::vec3(_max.x, _max.y, _min.z));
    mesh.addVertex(glm::vec3(_max.x, _max.y, _max.z));
    mesh.addVertex(glm::vec3(_min.x, _max.y, _min.z));
    mesh.addVertex(glm::vec3(_min.x, _max.y, _max.z));

    return mesh;
}

void BoundaryBox::draw() const
{
    ofSetColor(ofColor::green);
    ofSetLineWidth(1);
    ofNoFill();

    // face avant
    ofDrawLine(_min.x, _min.y, _min.z, _max.x, _min.y, _min.z);
    ofDrawLine(_max.x, _min.y, _min.z, _max.x, _max.y, _min.z);
    ofDrawLine(_max.x, _max.y, _min.z, _min.x, _max.y, _min.z);
    ofDrawLine(_min.x, _max.y, _min.z, _min.x, _min.y, _min.z);

    // face arrière
    ofDrawLine(_min.x, _min.y, _max.z, _max.x, _min.y, _max.z);
    ofDrawLine(_max.x, _min.y, _max.z, _max.x, _max.y, _max.z);
    ofDrawLine(_max.x, _max.y, _max.z, _min.x, _max.y, _max.z);
    ofDrawLine(_min.x, _max.y, _max.z, _min.x, _min.y, _max.z);

    // arêtes
    ofDrawLine(_min.x, _min.y, _min.z, _min.x, _min.y, _max.z);
    ofDrawLine(_max.x, _min.y, _min.z, _max.x, _min.y, _max.z);
    ofDrawLine(_max.x, _max.y, _min.z, _max.x, _max.y, _max.z);
    ofDrawLine(_min.x, _max.y, _min.z, _min.x, _max.y, _max.z);

    // diagonales
    ofDrawLine(_min.x, _min.y, _min.z, _max.x, _max.y, _max.z);
    ofDrawLine(_max.x, _min.y, _min.z, _min.x, _max.y, _max.z);
    ofDrawLine(_min.x, _min.y, _max.z, _max.x, _max.y, _min.z);
    ofDrawLine(_max.x, _min.y, _max.z, _min.x, _max.y, _min.z);

    // dessiner les sommets
    ofSetColor(ofColor::red);
    ofDrawSphere(_min.x, _min.y, _min.z, 2.0f);
    ofDrawSphere(_max.x, _min.y, _min.z, 2.0f);
    ofDrawSphere(_max.x, _max.y, _min.z, 2.0f);
    ofDrawSphere(_min.x, _max.y, _min.z, 2.0f);
    ofDrawSphere(_min.x, _min.y, _max.z, 2.0f);
    ofDrawSphere(_max.x, _min.y, _max.z, 2.0f);
    ofDrawSphere(_max.x, _max.y, _max.z, 2.0f);
    ofDrawSphere(_min.x, _max.y, _max.z, 2.0f);
}

} // namespace plugin::geometry
