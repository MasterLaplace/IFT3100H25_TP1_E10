#include "Point2D.hpp"

namespace plugin::primitive {

Point2D::Point2D(PrimitiveParams _params, float _size) : Primitive(_params) { size = _size; }

void Point2D::draw()
{
    ofPushMatrix();
    ofTranslate(param.position.x, param.position.y);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y);
    
    ofSetColor(param.fillColor);
    ofFill();
    ofDrawCircle(glm::vec3(0.0f), size);
    
    ofPopMatrix();
}

bool Point2D::isInside(const glm::vec3 &point)
{
    float distance = glm::distance(param.position, point);
    return distance < size;
}

} // namespace plugin::primitive
