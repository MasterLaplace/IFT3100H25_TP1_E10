#include "Ellipsoid.hpp"
#include "../image/ResourceManager.hpp"

namespace plugin::primitive {

Ellipsoid::Ellipsoid(PrimitiveParams params, glm::vec3 radius) : Primitive(params) { _radius = radius; }

void Ellipsoid::draw()
{
    ofEnableAntiAliasing();
    ofPushMatrix();
    ofTranslate(param.position);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y, param.scale.z);

    ofSetColor(param.ambientColor);
    ofSetLineWidth(1);
    ofFill();

    if (param.isFilled)
        drawFill();

    else
        drawOutline();

    ofPopMatrix();
    ofDisableAntiAliasing();
}

void Ellipsoid::setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) 
{
    setAmbientColor(ambient);
    setDiffuseColor(diffuse);
    setSpecularColor(specular);
    setShininess(shininess);
}

void Ellipsoid::drawFill()
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
    }

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    for (int i = 0; i <= _numStacks; ++i)
    {
        float lat0 = PI * (-0.5 + (float) (i - 1) / _numStacks);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = PI * (-0.5 + (float) i / _numStacks);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        for (int j = 0; j <= _numSlices; ++j)
        {
            float lng = 2 * PI * (float) (j - 1) / _numSlices;
            float x = cos(lng);
            float y = sin(lng);

            glm::vec3 v0 = glm::vec3(x * zr0 * _radius.x, y * zr0 * _radius.y, z0 * _radius.z);
            glm::vec3 v1 = glm::vec3(x * zr1 * _radius.x, y * zr1 * _radius.y, z1 * _radius.z);

            mesh.addVertex(v0);
            mesh.addVertex(v1);

            // Le calcule des normales.
            glm::vec3 n0 = glm::normalize(glm::vec3(x * zr0 / _radius.x, y * zr0 / _radius.y, z0 / _radius.z));
            glm::vec3 n1 = glm::normalize(glm::vec3(x * zr1 / _radius.x, y * zr1 / _radius.y, z1 / _radius.z));

            mesh.addNormal(n0);
            mesh.addNormal(n1);

            if (hasTexture)
            {
                float u0 = (float) j / _numSlices;
                float v0 = (float) (i - 1) / _numStacks;
                float u1 = (float) j / _numSlices;
                float v1 = (float) i / _numStacks;

                mesh.addTexCoord(ofVec2f(u0 * image->get()->getWidth(), v0 * image->get()->getHeight()));
                mesh.addTexCoord(ofVec2f(u1 * image->get()->getWidth(), v1 * image->get()->getHeight()));
            }
        }
    }

    for (size_t i = 0; i < mesh.getNumVertices() - 2; i += 2)
    {
        mesh.addIndex(i);
        mesh.addIndex(i + 1);
        mesh.addIndex(i + 2);

        mesh.addIndex(i + 1);
        mesh.addIndex(i + 2);
        mesh.addIndex(i + 3);
    }

    if (param.drawGizmo)
    {
        bbox.load(mesh);
        bbox.draw();
    }

    mesh.draw();

    if (hasTexture)
    {
        image->get()->getTexture().unbind();
    }
}

void Ellipsoid::drawOutline()
{
    // https://stackoverflow.com/questions/28806871/how-to-render-sphere-using-open-gl-c-and-not-glut-glu
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();

    for (int i = 0; i <= _numStacks; ++i)
    {
        float lat0 = PI * (-0.5 + (float) (i - 1) / _numStacks);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = PI * (-0.5 + (float) i / _numStacks);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        ofBeginShape();
        for (int j = 0; j <= _numSlices; ++j)
        {
            float lng = 2 * PI * (float) (j - 1) / _numSlices;
            float x = cos(lng);
            float y = sin(lng);

            ofVertex(x * zr0 * _radius.x, y * zr0 * _radius.y, z0 * _radius.z);
            ofVertex(x * zr1 * _radius.x, y * zr1 * _radius.y, z1 * _radius.z);
        }
        ofEndShape(true);
    }
}

bool Ellipsoid::isInside(const glm::vec3 &point)
{
    // Voici ma méthode pour trouver l'intérieur d'une ellipse modifiée pour une ellipsoide
    // https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse
    // (x - h)^2 / a^2 + (y - k)^2 / b^2 <= 1

    float a = _radius.x;
    float b = _radius.y;
    float c = _radius.z;
    float h = param.position.x;
    float k = param.position.y;
    float l = param.position.z;

    float x = point.x;
    float y = point.y;
    float z = point.z;

    float result = pow((x - h) / a, 2) + pow((y - k) / b, 2) + pow((z - l) / c, 2);

    if (result <= 1)
    {
        return true;
    }

    return false;
}

} // namespace plugin::primitive
