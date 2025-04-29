#include "MappingScene.hpp"

void MappingScene::setup()
{
    ofSetFrameRate(60);
    ofEnableDepthTest();

    // Charger les textures
    ofLoadImage(diffuseTexture, "mapping/diffuse.jpg");
    ofLoadImage(normalTexture, "mapping/normal.jpg");
    ofLoadImage(heightMap, "mapping/height.jpg");

    // Configuration du plane
    plane.set(400, 400, 200, 200);
    plane.setPosition(0, 0, 0);
    plane.mapTexCoordsFromTexture(diffuseTexture);
    plane.mapTexCoordsFromTexture(normalTexture);
    plane.mapTexCoordsFromTexture(heightMap);

    // Configuration du vboMesh pour avoir les tangentes
    vboMesh = plane.getMesh();
    calculateTangents();

    // Set up camera
    camera.setDistance(600);
    camera.setNearClip(10);
    camera.setFarClip(2000);

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

    currentMappingMethod = DIFFUSE;
    displacementScale = 5.0f;

    currentShader.load("mapping/diffuse/shader");
}

void MappingScene::calculateTangents()
{
    // Récupérer les données du mesh
    std::vector<glm::vec3> &vertices = plane.getMesh().getVertices();
    std::vector<glm::vec3> &normals = plane.getMesh().getNormals();
    std::vector<glm::vec2> &texCoords = plane.getMesh().getTexCoords();
    std::vector<ofIndexType> indices = plane.getMesh().getIndices();

    // Créer les vecteurs pour les tangentes et bitangentes
    std::vector<ofVec3f> tangents(vertices.size(), ofVec3f(0, 0, 0));
    std::vector<ofVec3f> bitangents(vertices.size(), ofVec3f(0, 0, 0));

    // Pour chaque triangle
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        if (i + 2 >= indices.size())
            continue;

        ofIndexType i1 = indices[i];
        ofIndexType i2 = indices[i + 1];
        ofIndexType i3 = indices[i + 2];

        glm::vec3 v1 = vertices[i1];
        glm::vec3 v2 = vertices[i2];
        glm::vec3 v3 = vertices[i3];

        glm::vec2 uv1 = texCoords[i1];
        glm::vec2 uv2 = texCoords[i2];
        glm::vec2 uv3 = texCoords[i3];

        // Calculer les différences
        glm::vec3 deltaPos1 = v2 - v1;
        glm::vec3 deltaPos2 = v3 - v1;

        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        // Calculer la tangente et la bitangente
        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        if (std::isfinite(r))
        { // Vérifier que r n'est pas inf ou NaN
            glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;

            // Ajouter aux vecteurs
            tangents[i1] += tangent;
            tangents[i2] += tangent;
            tangents[i3] += tangent;
        }
    }

    // Orthogonaliser et normaliser les tangentes
    for (size_t i = 0; i < vertices.size(); i++)
    {
        ofVec3f n = normals[i];
        ofVec3f t = tangents[i];

        // Orthogonaliser la tangente par rapport à la normale (Gram-Schmidt)
        t = (t - n * n.dot(t)).normalize();
    }

    vboMesh.getVbo().setAttributeData(10, &tangents[0].x, 3, tangents.size(), GL_STATIC_DRAW);
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
        vboMesh.draw();
        ofPopMatrix();

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
