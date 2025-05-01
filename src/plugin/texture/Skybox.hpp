#pragma once

#include "ofMain.h"
#include "plugin/image/ResourceManager.hpp"

namespace plugin::texture {

class Skybox {
public:
    Skybox();

    void draw(glm::vec3 position);
    void load(std::string resourceName);

private:
    std::array<ofTexture, 6> textures;
    std::array<ofPlanePrimitive, 6> planes;
    ofShader shader;
    bool isLoaded = false;
};

} // namespace plugin::texture
