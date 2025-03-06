#include "Rectangle.hpp"
#include "../image/ResourceManager.hpp"

namespace plugin::primitive {

Rectangle::Rectangle(PrimitiveParams _params, glm::vec2 _dimensions) : Primitive(_params) { dimensions = _dimensions; }

void Rectangle::draw()
{
    ofPushMatrix();
    ofTranslate(param.position.x, param.position.y);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y);

    (param.isFilled) ? drawFill() : drawOutline();

    ofPopMatrix();
}

void Rectangle::drawFill()
{
    bool hasTexture = false;
    std::optional<std::shared_ptr<ofImage>> image;
    if (!param.imageName.empty())
    {
        image = image::ResourceManager::instance()->getImage(param.imageName);
        if (image.has_value())
        {
            ofSetColor(255);
            image->get()->getTexture().bind();
            hasTexture = true;
        }
        else
        {
            ofSetColor(param.fillColor);
            ofSetLineWidth(1);
            ofFill();
        }
    }

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    mesh.addVertex(glm::vec3(0, 0, 0));
    mesh.addVertex(glm::vec3(dimensions.x, 0, 0));
    mesh.addVertex(glm::vec3(dimensions.x, dimensions.y, 0));
    mesh.addVertex(glm::vec3(0, dimensions.y, 0));

    if (hasTexture)
    {
        mesh.addTexCoord(glm::vec2(0, 0));
        mesh.addTexCoord(glm::vec2(image->get()->getWidth(), 0));
        mesh.addTexCoord(glm::vec2(image->get()->getWidth(), image->get()->getHeight()));
        mesh.addTexCoord(glm::vec2(0, image->get()->getHeight()));
    }

    mesh.draw();

    if (hasTexture)
    {
        image->get()->getTexture().unbind();
    }
}

void Rectangle::drawOutline()
{
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();

    ofDrawRectangle(0, 0, dimensions.x, dimensions.y);
}

bool Rectangle::isInside(const glm::vec3 &point)
{
    return point.x > param.position.x && point.x < param.position.x + dimensions.x && point.y > param.position.y &&
           point.y < param.position.y + dimensions.y;
}

} // namespace plugin::primitive
