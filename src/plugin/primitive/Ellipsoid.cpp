#include "Ellipsoid.hpp"

namespace plugin::primitive {

Ellipsoid::Ellipsoid(PrimitiveParams params, glm::vec3 radius, int numSlices, int numStacks) : Primitive(params)
{
    _radius = radius;
    _numSlices = numSlices;
    _numStacks = numStacks;
}

void Ellipsoid::draw()
{
    ofEnableAntiAliasing();
    (param.isFilled) ? drawFill() : drawOutline();
    ofDisableAntiAliasing();
}

void Ellipsoid::drawFill()
{
    ofPushMatrix();
    ofTranslate(param.position);
    ofSetColor(param.fillColor);
    ofSetLineWidth(1);
    ofFill();

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

    ofPopMatrix();
}

void Ellipsoid::drawOutline()
{
    // https://stackoverflow.com/questions/28806871/how-to-render-sphere-using-open-gl-c-and-not-glut-glu
    ofPushMatrix();
    ofTranslate(param.position);
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

    ofPopMatrix();
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
