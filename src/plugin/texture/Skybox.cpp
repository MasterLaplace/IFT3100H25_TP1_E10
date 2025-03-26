#include "Skybox.hpp"

namespace plugin::texture {

Skybox::Skybox()
{
    // Create six planes, each for a face of the cube
    for (int i = 0; i < 6; ++i)
    {
        planes[i].set(2000, 2000); // Set the size of each plane (same as the cube's size)
    }
}

void Skybox::load(std::string resourceName)
{
    using namespace plugin::image;
    auto resourceTextures = ResourceManager::instance()->getCubeMap(resourceName);

    if (!resourceTextures.has_value())
    {
        std::cerr << "Skybox Error: Could not load cube map: " << resourceName << std::endl;
        return;
    }

    auto texturesArray = resourceTextures.value();

    if (texturesArray->size() < 6)
    {
        std::cerr << "Skybox Error: Not enough textures for a full skybox!" << std::endl;
        return;
    }

    textures = *texturesArray;

    // Flip the textures using rotate90Degs
    for (auto &texture : textures)
    {
        ofPixels pixels;
        texture.readToPixels(pixels);
        pixels.rotate90(2); // Rotate 180 degrees (2 * 90 degrees)
        texture.loadData(pixels);
    }

    isLoaded = true;
}

void Skybox::draw(glm::vec3 position)
{
    if (!isLoaded)
        return;

    ofDisableDepthTest();
    ofEnableArbTex();
    ofEnableNormalizedTexCoords();
    ofSetColor(255);

    // Draw each plane with the corresponding texture
    for (int i = 0; i < 6; ++i)
    {
        textures[i].bind();

        // Reset transformations before applying new ones
        planes[i].resetTransform();

        int size = 1000;
        // Set position and rotation for each plane
        switch (i)
        {
        case 0: // Left
            planes[i].setPosition(position.x - size, position.y, position.z);
            planes[i].rotateDeg(-90, 0, 1, 0);
            break;
        case 3: // Front
            planes[i].setPosition(position.x, position.y, position.z + size);
            break;
        case 2: // Right
            planes[i].setPosition(position.x + size, position.y, position.z);
            planes[i].rotateDeg(90, 0, 1, 0);
            break;
        case 1: // Back
            planes[i].setPosition(position.x, position.y, position.z - size);
            planes[i].rotateDeg(180, 0, 1, 0);
            break;
        case 4: // Top
            planes[i].setPosition(position.x, position.y - size, position.z);
            planes[i].rotateDeg(-90, 1, 0, 0);
            planes[i].rotateDeg(180, 0, 0, 1);
            break;
        case 5: // Bottom
            planes[i].setPosition(position.x, position.y + size, position.z);
            planes[i].rotateDeg(90, 1, 0, 0);
            planes[i].rotateDeg(180, 0, 0, 1);
            break;
        }

        planes[i].draw();
        textures[i].unbind();
    }

    ofEnableDepthTest();
    ofDisableNormalizedTexCoords();
    ofDisableArbTex();
}

} // namespace plugin::texture
