#include "Ellipse.hpp"
#include "../image/ResourceManager.hpp"

namespace plugin::primitive {

Ellipse::Ellipse(PrimitiveParams _params, glm::vec2 _radius) : Primitive(_params) { radius = _radius; }

void Ellipse::draw()
{
    ofPushMatrix();
    ofTranslate(param.position.x, param.position.y);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y);

    ofEnableAntiAliasing();
    if (param.isFilled)
        drawFill();
    drawOutline();
    ofDisableAntiAliasing();

    ofPopMatrix();
}

void Ellipse::drawOutline()
{
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();

    ofDrawEllipse(0, 0, radius.x, radius.y);
}

void Ellipse::drawFill()
{
    bool hasTexture = false;
    std::optional<std::shared_ptr<ofImage>> image;
    if (!param.imageName.empty())
    {
        image = image::ResourceManager::instance()->getImage(param.imageName);
        if (image.has_value())
        {
            ofSetColor(255);
            ofSetLineWidth(1);
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

    if (hasTexture)
        mesh.addTexCoord(glm::vec2(image->get()->getWidth() / 2, image->get()->getHeight() / 2));

    int numSegments = 100;
    for (int i = 0; i <= numSegments; ++i)
    {
        float theta = 2.0f * PI * float(i) / float(numSegments);
        float x = radius.x * 0.5f * cosf(theta);
        float y = radius.y * 0.5f * sinf(theta);

        mesh.addVertex(glm::vec3(x, y, 0));
        if (hasTexture)
        {
            float u = (x / radius.x + 1.0f) * 0.5f * image->get()->getWidth();
            float v = (y / radius.y + 1.0f) * 0.5f * image->get()->getHeight();
            mesh.addTexCoord(glm::vec2(u, v));
        }
    }

    mesh.draw();

    if (hasTexture)
        image->get()->getTexture().unbind();
}

bool Ellipse::isInside(const glm::vec3 &point)
{
    // Voici ma méthode pour trouver l'intérieur d'une ellipse.
    // https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse
    // (x - h)^2 / a^2 + (y - k)^2 / b^2 <= 1

    float a = radius.x;
    float b = radius.y;
    float h = param.position.x;
    float k = param.position.y;

    float x = point.x;
    float y = point.y;

    float result = pow((x - h) / a, 2) + pow((y - k) / b, 2);

    if (result <= 1)
    {
        return true;
    }

    return false;
}

} // namespace plugin::primitive
