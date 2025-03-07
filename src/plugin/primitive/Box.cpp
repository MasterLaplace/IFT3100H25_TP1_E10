#include "Box.hpp"
#include "../image/ResourceManager.hpp"

namespace plugin::primitive {

Box::Box(PrimitiveParams param, glm::vec3 size) : Primitive(param), _size(size) {}

void Box::draw()
{
    ofPushMatrix();
    ofTranslate(param.position);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y, param.scale.z);

    ofSetColor(param.fillColor);
    ofSetLineWidth(1);
    ofFill();

    if (param.isFilled)
        drawFill();

    drawOutline();

    ofPopMatrix();
}

void Box::drawFill()
{
    bool hasTexture = false;
    std::optional<std::shared_ptr<ofImage>> opt_image;
    std::shared_ptr<ofImage> img;
    if (!param.imageName.empty())
    {
        opt_image = image::ResourceManager::instance()->getImage(param.imageName);
        if (opt_image.has_value())
        {
            ofSetColor(255);
            opt_image->get()->getTexture().bind();
            img = *opt_image;
            hasTexture = true;
        }
    }

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    float halfWidth = _size.x / 2.0f;
    float halfHeight = _size.y / 2.0f;
    float halfDepth = _size.z / 2.0f;

    // Définition des sommets
    std::array<glm::vec3, 24> vertices = {
        // Front face
        glm::vec3(-halfWidth, -halfHeight, halfDepth),
        {halfWidth,  -halfHeight, halfDepth },
        {halfWidth,  halfHeight,  halfDepth },
        {-halfWidth, halfHeight,  halfDepth },

        // Back face
        {-halfWidth, -halfHeight, -halfDepth},
        {halfWidth,  -halfHeight, -halfDepth},
        {halfWidth,  halfHeight,  -halfDepth},
        {-halfWidth, halfHeight,  -halfDepth},

        // Left face
        {-halfWidth, -halfHeight, -halfDepth},
        {-halfWidth, -halfHeight, halfDepth },
        {-halfWidth, halfHeight,  halfDepth },
        {-halfWidth, halfHeight,  -halfDepth},

        // Right face
        {halfWidth,  -halfHeight, -halfDepth},
        {halfWidth,  -halfHeight, halfDepth },
        {halfWidth,  halfHeight,  halfDepth },
        {halfWidth,  halfHeight,  -halfDepth},

        // Top face
        {-halfWidth, halfHeight,  -halfDepth},
        {halfWidth,  halfHeight,  -halfDepth},
        {halfWidth,  halfHeight,  halfDepth },
        {-halfWidth, halfHeight,  halfDepth },

        // Bottom face
        {-halfWidth, -halfHeight, -halfDepth},
        {halfWidth,  -halfHeight, -halfDepth},
        {halfWidth,  -halfHeight, halfDepth },
        {-halfWidth, -halfHeight, halfDepth }
    };

    for (const auto &v : vertices)
    {
        mesh.addVertex(v);
    }

    std::vector<unsigned int> indices = {
        0,  1,  2,  0,  2,  3,  // Front
        4,  6,  5,  4,  7,  6,  // Back
        8,  9,  10, 8,  10, 11, // Left
        12, 14, 13, 12, 15, 14, // Right
        16, 17, 18, 16, 18, 19, // Top
        20, 22, 21, 20, 23, 22  // Bottom
    };

    for (const auto &i : indices)
    {
        mesh.addIndex(i);
    }

    if (hasTexture)
    {
        for (int i = 0; i < 6; i++)
        {
            mesh.addTexCoord(glm::vec2(0, 0));
            mesh.addTexCoord(glm::vec2(img->getWidth(), 0));
            mesh.addTexCoord(glm::vec2(img->getWidth(), img->getHeight()));
            mesh.addTexCoord(glm::vec2(0, img->getHeight()));
        }
    }

    mesh.draw();

    if (hasTexture)
    {
        img->getTexture().unbind();
    }
}

void Box::drawOutline()
{
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();

    drawBox();
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
