#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "plugin/image/ResourceManager.hpp"
#include "plugin/raytracing/Raytracing.hpp"

using namespace plugin;

class RaytracingScene {
public:
    void setup(const raytracing::Raytracing::CreateInfo &params,
               const std::vector<std::shared_ptr<primitive::Primitive>> &primitives);
    void draw();

private:
    void drawGui();

    void init_cornell_box();

    void updateScene();

    void exportImage(const std::string &filename);

private:
    std::unique_ptr<raytracing::Raytracing> _raytracer;
    image::Image _image;
    std::vector<std::shared_ptr<primitive::Primitive>> _scene;

    glm::dvec3 _position;
    glm::dvec3 _direction;
    glm::dvec3 _background_color;
    double _fov;
    uint32_t _depth;
    uint32_t _width;
    uint32_t _height;
    uint32_t _ray_per_pixel;
};
