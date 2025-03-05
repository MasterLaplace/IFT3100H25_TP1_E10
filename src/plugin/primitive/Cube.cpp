#include "Cube.hpp"

namespace plugin::primitive {

Cube::Cube(PrimitiveParams param, float _size) : Primitive(param), size(_size) {}

void Cube::draw()
{
    ofSetColor(param.fillColor);
    ofPushMatrix();
    ofTranslate(param.position.x, param.position.y, param.position.z);
    ofDrawBox(size);
    ofPopMatrix();
}

bool Cube::isInside(const glm::vec3 &point) { return false; }

} // namespace plugin::primitive
