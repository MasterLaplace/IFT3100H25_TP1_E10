#pragma once

#include "ofMain.h"
#include "plugin/image/ResourceManager.hpp"

namespace plugin::texture {

class Skybox {
public:
    Skybox();
    // Commentaire

    void draw(glm::vec3 position);       // Draw the skybox at the given position
    void load(std::string resourceName); // Load the textures for the skybox

private:
    std::array<ofTexture, 6> textures;      // Store the six textures for each face of the cube
    std::array<ofPlanePrimitive, 6> planes; // Create six planes for each face of the skybox
    ofShader shader;                        // Shader for rendering (you can update it as needed)
    bool isLoaded = false;                  // Flag to check if the textures are loaded
};

} // namespace plugin::texture
