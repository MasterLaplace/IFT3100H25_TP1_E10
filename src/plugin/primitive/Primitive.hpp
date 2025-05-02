#pragma once

#include "ofMain.h"
#include "plugin/geometry/BoundaryBox.hpp"

namespace plugin::primitive {

enum class SurfaceType : uint8_t {
    DIFFUSE,
    SPECULAR,
    REFRACTION
};

struct PrimitiveParams {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    float outlineWidth;
    bool isFilled;
    ofColor fillColor;
    ofColor outlineColor;
    ofColor ambientColor;
    ofColor diffuseColor;
    ofColor specularColor;
    float shininess;
    std::string imageName = "";
    bool drawGizmo = false;
    SurfaceType material = SurfaceType::DIFFUSE; // type de réflexion de la primitive
    glm::dvec3 emission{1.0};

    PrimitiveParams()
        : outlineWidth(1.0f), isFilled(true), fillColor(ofColor::white), outlineColor(ofColor::black),
          ambientColor(ofColor::black), diffuseColor(ofColor::lightGray), specularColor(ofColor::white),
          shininess(32.0f)
    {
    }

    PrimitiveParams(glm::dvec3 position, glm::dvec3 fillColor, SurfaceType material, glm::dvec3 emission)
        : position(position), fillColor(ofColor(fillColor.x, fillColor.y, fillColor.z)), material(material),
          emission(emission)
    {
    }
};

class Primitive {
public:
    Primitive(const PrimitiveParams &params) : param(params) {}
    Primitive(const Primitive &other) = default;
    Primitive(Primitive &&other) = default;
    virtual ~Primitive() = default;

    virtual std::shared_ptr<Primitive> clone() const = 0;

    virtual void draw() = 0;
    virtual bool isInside(const glm::vec3 &point) = 0;

    [[nodiscard]] inline const geometry::BoundaryBox &getBoundaryBox() const { return _bbox; }

    PrimitiveParams param;
    geometry::BoundaryBox _bbox;
};

} // namespace plugin::primitive
