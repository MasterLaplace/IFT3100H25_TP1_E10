#include "Box.hpp"

namespace plugin::primitive {

Box::Box(PrimitiveParams param, glm::vec3 size) : Primitive(param), _size(size) {}

void Box::draw() { (param.isFilled) ? drawFill() : drawOutline(); }

void Box::drawFill()
{
    ofSetColor(param.fillColor);

    ofPushMatrix();
    ofTranslate(param.position);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y, param.scale.z);

    drawBox();

    ofPopMatrix();
}

void Box::drawOutline()
{
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();

    ofPushMatrix();
    ofTranslate(param.position);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y, param.scale.z);

    drawBox();

    ofPopMatrix();
}

bool Box::isInside(const glm::vec3 &point)
{
    return point.x >= param.position.x - _size.x / 2.0f && point.x <= param.position.x + _size.x / 2.0f &&
           point.y >= param.position.y - _size.y / 2.0f && point.y <= param.position.y + _size.y / 2.0f &&
           point.z >= param.position.z - _size.z / 2.0f && point.z <= param.position.z + _size.z / 2.0f;
}

void Box::drawBox()
{
    float halfWidth = _size.x / 2.0f;
    float halfHeight = _size.y / 2.0f;
    float halfDepth = _size.z / 2.0f;

    // Front face
    ofBeginShape();
    ofVertex(-halfWidth, -halfHeight, halfDepth);
    ofVertex(halfWidth, -halfHeight, halfDepth);
    ofVertex(halfWidth, halfHeight, halfDepth);
    ofVertex(-halfWidth, halfHeight, halfDepth);
    ofEndShape(true);

    // Back face
    ofBeginShape();
    ofVertex(-halfWidth, -halfHeight, -halfDepth);
    ofVertex(halfWidth, -halfHeight, -halfDepth);
    ofVertex(halfWidth, halfHeight, -halfDepth);
    ofVertex(-halfWidth, halfHeight, -halfDepth);
    ofEndShape(true);

    // Left face
    ofBeginShape();
    ofVertex(-halfWidth, -halfHeight, -halfDepth);
    ofVertex(-halfWidth, -halfHeight, halfDepth);
    ofVertex(-halfWidth, halfHeight, halfDepth);
    ofVertex(-halfWidth, halfHeight, -halfDepth);
    ofEndShape(true);

    // Right face
    ofBeginShape();
    ofVertex(halfWidth, -halfHeight, -halfDepth);
    ofVertex(halfWidth, -halfHeight, halfDepth);
    ofVertex(halfWidth, halfHeight, halfDepth);
    ofVertex(halfWidth, halfHeight, -halfDepth);
    ofEndShape(true);

    // Top face
    ofBeginShape();
    ofVertex(-halfWidth, halfHeight, -halfDepth);
    ofVertex(halfWidth, halfHeight, -halfDepth);
    ofVertex(halfWidth, halfHeight, halfDepth);
    ofVertex(-halfWidth, halfHeight, halfDepth);
    ofEndShape(true);

    // Bottom face
    ofBeginShape();
    ofVertex(-halfWidth, -halfHeight, -halfDepth);
    ofVertex(halfWidth, -halfHeight, -halfDepth);
    ofVertex(halfWidth, -halfHeight, halfDepth);
    ofVertex(-halfWidth, -halfHeight, halfDepth);
    ofEndShape(true);
}

} // namespace plugin::primitive
