#include "Cube.hpp"

namespace plugin::primitive {

Cube::Cube(PrimitiveParams param, float _size) : Primitive(param), size(_size) {}

void Cube::draw() { (param.isFilled) ? drawFill() : drawOutline(); }

void Cube::drawFill()
{
    ofSetColor(param.fillColor);
    ofPushMatrix();
    ofTranslate(param.position);

    float halfSize = size / 2.0f;

    // Front face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, halfSize);
    ofVertex(halfSize, -halfSize, halfSize);
    ofVertex(halfSize, halfSize, halfSize);
    ofVertex(-halfSize, halfSize, halfSize);
    ofEndShape(true);

    // Back face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, halfSize, -halfSize);
    ofVertex(-halfSize, halfSize, -halfSize);
    ofEndShape(true);

    // Left face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, -halfSize);
    ofVertex(-halfSize, -halfSize, halfSize);
    ofVertex(-halfSize, halfSize, halfSize);
    ofVertex(-halfSize, halfSize, -halfSize);
    ofEndShape(true);

    // Right face
    ofBeginShape();
    ofVertex(halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, halfSize);
    ofVertex(halfSize, halfSize, halfSize);
    ofVertex(halfSize, halfSize, -halfSize);
    ofEndShape(true);

    // Top face
    ofBeginShape();
    ofVertex(-halfSize, halfSize, -halfSize);
    ofVertex(halfSize, halfSize, -halfSize);
    ofVertex(halfSize, halfSize, halfSize);
    ofVertex(-halfSize, halfSize, halfSize);
    ofEndShape(true);

    // Bottom face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, halfSize);
    ofVertex(-halfSize, -halfSize, halfSize);
    ofEndShape(true);

    ofPopMatrix();
}

void Cube::drawOutline()
{
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(param.position);

    float halfSize = size / 2.0f;

    // Front face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, halfSize);
    ofVertex(halfSize, -halfSize, halfSize);
    ofVertex(halfSize, halfSize, halfSize);
    ofVertex(-halfSize, halfSize, halfSize);
    ofEndShape(true);

    // Back face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, halfSize, -halfSize);
    ofVertex(-halfSize, halfSize, -halfSize);
    ofEndShape(true);

    // Left face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, -halfSize);
    ofVertex(-halfSize, -halfSize, halfSize);
    ofVertex(-halfSize, halfSize, halfSize);
    ofVertex(-halfSize, halfSize, -halfSize);
    ofEndShape(true);

    // Right face
    ofBeginShape();
    ofVertex(halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, halfSize);
    ofVertex(halfSize, halfSize, halfSize);
    ofVertex(halfSize, halfSize, -halfSize);
    ofEndShape(true);

    // Top face
    ofBeginShape();
    ofVertex(-halfSize, halfSize, -halfSize);
    ofVertex(halfSize, halfSize, -halfSize);
    ofVertex(halfSize, halfSize, halfSize);
    ofVertex(-halfSize, halfSize, halfSize);
    ofEndShape(true);

    // Bottom face
    ofBeginShape();
    ofVertex(-halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, -halfSize);
    ofVertex(halfSize, -halfSize, halfSize);
    ofVertex(-halfSize, -halfSize, halfSize);
    ofEndShape(true);

    ofPopMatrix();
}

bool Cube::isInside(const glm::vec3 &point)
{
    return point.x >= param.position.x - size / 2.0f && point.x <= param.position.x + size / 2.0f &&
           point.y >= param.position.y - size / 2.0f && point.y <= param.position.y + size / 2.0f &&
           point.z >= param.position.z - size / 2.0f && point.z <= param.position.z + size / 2.0f;
}

} // namespace plugin::primitive
