#include "MappingScene.hpp"

void MappingScene::setup()
{
    ofSetFrameRate(60);
    ofEnableDepthTest();

    // Set up plane geometry
    plane.set(400, 400, 200, 200);
    plane.setPosition(0, 0, 0);

    // Set up camera
    camera.setDistance(600);
    camera.setNearClip(10);
    camera.setFarClip(2000);
    rotation = ofQuaternion(0, 0, 0, 1);
    currentRotation = ofQuaternion(0, 0, 0, 1);
    dragging = false;

    // Charger les textures
    ofLoadImage(diffuseTexture, "mapping/diffuse.jpg");
    ofLoadImage(normalTexture, "mapping/normal.jpg");
    ofLoadImage(heightMap, "mapping/height.jpg");

    // S'assurer que heightMap est en niveaux de gris
    // Cela pourrait aider avec le problème de pics
    ofPixels pixels;
    heightMap.readToPixels(pixels);
    if (pixels.getNumChannels() > 1)
    {
        ofPixels grayPixels;
        grayPixels.allocate(pixels.getWidth(), pixels.getHeight(), OF_PIXELS_GRAY);
        for (int y = 0; y < pixels.getHeight(); y++)
        {
            for (int x = 0; x < pixels.getWidth(); x++)
            {
                ofColor color = pixels.getColor(x, y);
                float gray = color.getBrightness();
                grayPixels.setColor(x, y, ofColor(gray));
            }
        }
        heightMap.allocate(grayPixels);
    }

    // Configurer les paramètres de texture pour la heightMap
    heightMap.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
    heightMap.setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

    // Mapper les coordonnées de texture pour le plane
    plane.mapTexCoordsFromTexture(diffuseTexture);

    currentMappingMethod = DIFFUSE;
    displacementScale = 5.0f;

    currentShader.load("mapping/diffuse/shader");
}

void MappingScene::update()
{

}

void MappingScene::draw()
{
    plane.enableTextures();
    ofBackground(40);

    camera.begin();
    if (ImGui::GetIO().WantCaptureMouse)
    {
        camera.disableMouseInput();
    }
    else
    {
        camera.enableMouseInput();
    }

    ofSetColor(255);

    // Use shader and draw plane
    if (currentShader.isLoaded())
    {
        currentShader.begin();

        // Assignation des textures aux unités appropriées
        currentShader.setUniformTexture("diffuseTexture", diffuseTexture, 0);

        switch (currentMappingMethod)
        {
        case DISPLACEMENT:
            currentShader.setUniformTexture("heightMap", heightMap, 1);
            currentShader.setUniform1f("displacementScale", displacementScale);
            break;
        case NORMAL:
            currentShader.setUniformTexture("normalTexture", normalTexture, 1);

            // Envoyer les paramètres de lumière pour le normal mapping
            currentShader.setUniform3f("lightDir", lightDirection.x, lightDirection.y, lightDirection.z);
            currentShader.setUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
            currentShader.setUniform1f("ambientStrength", ambientStrength);
            break;
        case PARALLAX: break;
        }

        // Calcul et envoi des matrices au shader
        ofMatrix4x4 modelViewMatrix = camera.getModelViewMatrix();
        ofMatrix4x4 projectionMatrix = camera.getProjectionMatrix();
        ofMatrix4x4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

        currentShader.setUniformMatrix4f("modelViewMatrix", modelViewMatrix);
        currentShader.setUniformMatrix4f("projectionMatrix", projectionMatrix);
        currentShader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);

        // Dessiner le plane
        ofPushMatrix();
        plane.draw();
        ofPopMatrix();

        // Débinder les textures
        if (currentMappingMethod == DISPLACEMENT)
        {
            heightMap.unbind(1);
        }
        else if (currentMappingMethod == NORMAL)
        {
            normalTexture.unbind(1);
        }
        diffuseTexture.unbind(0);

        currentShader.end();
    }

    camera.end();

    ImGui::Begin("Mapping Options");
    const char *mappingOptions[] = {"diffuse", "displacement", "normal", "parallax"};
    int selectedOption = static_cast<int>(currentMappingMethod);
    if (ImGui::Combo("Mapping Method", &selectedOption, mappingOptions, IM_ARRAYSIZE(mappingOptions)))
    {
        currentMappingMethod = static_cast<MappingMethod>(selectedOption);
        currentShader.load("mapping/" + std::string(mappingOptions[selectedOption]) + "/shader");
    }

    // Ajouter un slider pour contrôler l'intensité du déplacement
    if (currentMappingMethod == DISPLACEMENT)
    {
        float displacementScale = this->displacementScale;
        if (ImGui::SliderFloat("Displacement Scale", &displacementScale, 0.0f, 100.0f))
        {
            this->displacementScale = displacementScale;
        }
    }

    if (currentMappingMethod == NORMAL)
    {
        if (ImGui::TreeNode("Lighting Settings"))
        {
            // Direction de la lumière
            float direction[3] = {lightDirection.x, lightDirection.y, lightDirection.z};
            if (ImGui::SliderFloat3("Light Direction", direction, -1.0f, 1.0f))
            {
                lightDirection = glm::normalize(glm::vec3(direction[0], direction[1], direction[2]));
            }

            // Couleur de la lumière
            float color[3] = {lightColor.x, lightColor.y, lightColor.z};
            if (ImGui::ColorEdit3("Light Color", color))
            {
                lightColor = glm::vec3(color[0], color[1], color[2]);
            }

            // Force ambiante
            if (ImGui::SliderFloat("Ambient Strength", &ambientStrength, 0.0f, 1.0f))
            {
                // La valeur est déjà mise à jour directement dans ambientStrength
            }

            ImGui::TreePop();
        }
    }

    ImGui::End();
}