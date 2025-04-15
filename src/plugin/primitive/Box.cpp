#include "Box.hpp"
#include "../image/ResourceManager.hpp"

namespace plugin::primitive {

Box::Box(PrimitiveParams param, glm::vec3 size) : Primitive(param), _size(size) {}

void Box::draw()
{
    ofEnableAntiAliasing();
    ofPushMatrix();
    ofTranslate(param.position);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y, param.scale.z);

    if (param.drawGizmo)
    {
        ofSetColor(ofColor::green);
        ofSetLineWidth(1);
        ofNoFill();

        drawBox();
    }

    ofSetColor(param.fillColor);
    ofSetLineWidth(1);
    ofFill();

    if (param.isFilled)
        drawFill();

    else
        drawOutline();

    ofPopMatrix();
    ofDisableAntiAliasing();
}

void Box::setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) 
{
    setAmbientColor(ambient);
    setDiffuseColor(diffuse);
    setSpecularColor(specular);
    setShininess(shininess);
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
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    glm::vec3 halfSize = _size * 0.5f;

    // Definition des sommets
    std::array<glm::vec3, 24> vertices = {
        // Front face
        glm::vec3(-halfSize.x, -halfSize.y, halfSize.z),
        {halfSize.x,  -halfSize.y, halfSize.z },
        {halfSize.x,  halfSize.y,  halfSize.z },
        {-halfSize.x, halfSize.y,  halfSize.z },
        // Back face
        {-halfSize.x, -halfSize.y, -halfSize.z},
        {halfSize.x,  -halfSize.y, -halfSize.z},
        {halfSize.x,  halfSize.y,  -halfSize.z},
        {-halfSize.x, halfSize.y,  -halfSize.z},
        // Left face
        {-halfSize.x, -halfSize.y, -halfSize.z},
        {-halfSize.x, -halfSize.y, halfSize.z },
        {-halfSize.x, halfSize.y,  halfSize.z },
        {-halfSize.x, halfSize.y,  -halfSize.z},
        // Right face
        {halfSize.x,  -halfSize.y, -halfSize.z},
        {halfSize.x,  -halfSize.y, halfSize.z },
        {halfSize.x,  halfSize.y,  halfSize.z },
        {halfSize.x,  halfSize.y,  -halfSize.z},
        // Top face
        {-halfSize.x, halfSize.y,  -halfSize.z},
        {halfSize.x,  halfSize.y,  -halfSize.z},
        {halfSize.x,  halfSize.y,  halfSize.z },
        {-halfSize.x, halfSize.y,  halfSize.z },
        // Bottom face
        {-halfSize.x, -halfSize.y, -halfSize.z},
        {halfSize.x,  -halfSize.y, -halfSize.z},
        {halfSize.x,  -halfSize.y, halfSize.z },
        {-halfSize.x, -halfSize.y, halfSize.z }
    };

    // Definition des normales
    std::array<glm::vec3, 24> normals = {
        // Front face
        glm::vec3(0.0f, 0.0f, 1.0f),
        {0.0f,  0.0f,  1.0f },
        {0.0f,  0.0f,  1.0f },
        {0.0f,  0.0f,  1.0f },
        // Back face
        {0.0f,  0.0f,  -1.0f},
        {0.0f,  0.0f,  -1.0f},
        {0.0f,  0.0f,  -1.0f},
        {0.0f,  0.0f,  -1.0f},
        // Left face
        {-1.0f, 0.0f,  0.0f },
        {-1.0f, 0.0f,  0.0f },
        {-1.0f, 0.0f,  0.0f },
        {-1.0f, 0.0f,  0.0f },
        // Right face
        {1.0f,  0.0f,  0.0f },
        {1.0f,  0.0f,  0.0f },
        {1.0f,  0.0f,  0.0f },
        {1.0f,  0.0f,  0.0f },
        // Top face
        {0.0f,  1.0f,  0.0f },
        {0.0f,  1.0f,  0.0f },
        {0.0f,  1.0f,  0.0f },
        {0.0f,  1.0f,  0.0f },
        // Bottom face
        {0.0f,  -1.0f, 0.0f },
        {0.0f,  -1.0f, 0.0f },
        {0.0f,  -1.0f, 0.0f },
        {0.0f,  -1.0f, 0.0f }
    };

    // Ajout des sommets et des normales au mesh
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        mesh.addVertex(vertices[i]);
        mesh.addNormal(normals[i]);
    }

    // Definition des indices
    std::array<ofIndexType, 36> indices = {// Front face
                                           0, 1, 2, 2, 3, 0,
                                           // Back face
                                           4, 5, 6, 6, 7, 4,
                                           // Left face
                                           8, 9, 10, 10, 11, 8,
                                           // Right face
                                           12, 13, 14, 14, 15, 12,
                                           // Top face
                                           16, 17, 18, 18, 19, 16,
                                           // Bottom face
                                           20, 21, 22, 22, 23, 20};

    // Ajout des indices au mesh
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
