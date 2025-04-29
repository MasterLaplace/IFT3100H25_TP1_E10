#include "MappingScene.hpp"

void MappingScene::setup()
{
    ofSetFrameRate(60);
    ofEnableDepthTest();

    // Charger les textures
    ofLoadImage(diffuseTexture, "mapping/diffuse.jpg");
    ofLoadImage(normalTexture, "mapping/normal_2.jpg");
    ofLoadImage(heightMap, "mapping/height.jpg");

    // Configuration du plane
    plane.set(400, 400, 200, 200);
    plane.setPosition(0, 0, 0);
    plane.mapTexCoordsFromTexture(diffuseTexture);
    plane.mapTexCoordsFromTexture(normalTexture);
    plane.mapTexCoordsFromTexture(heightMap);

    // Configuration de la lumière
    lightPosition = glm::vec3(100.0f, 100.0f, 100.0f); // Direction de la lumière
    lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Couleur blanche
    ambientStrength = 0.1f;  

    sphere.setRadius(10);

    // Configuration du vboMesh pour avoir les tangentes
    vboMesh = plane.getMesh();
    calculateTangents();

    // Set up camera
    camera.setDistance(600);
    camera.setNearClip(10);
    camera.setFarClip(2000);
    camera.setPosition(0, 0, 600);
    camera.lookAt(glm::vec3(0, 0, 0));

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

    ofSetColor(255);
    sphere.setPosition(lightPosition);
    sphere.draw();

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
            currentShader.setUniformTexture("normalMap", normalTexture, 1);
            break;
        }

        // Envoyer les paramètres de lumière
        currentShader.setUniform3f("lightPos", lightPosition.x, lightPosition.y, lightPosition.z);
        currentShader.setUniform3f("viewPos", camera.getGlobalPosition().x, camera.getGlobalPosition().y, camera.getGlobalPosition().z);
        currentShader.setUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
        currentShader.setUniform1f("ambientStrength", ambientStrength);

        // Calcul et envoi des matrices au shader
        ofMatrix4x4 modelMatrix = plane.getGlobalTransformMatrix();
        ofMatrix4x4 modelViewMatrix = camera.getModelViewMatrix();
        ofMatrix4x4 projectionMatrix = camera.getProjectionMatrix();
        ofMatrix4x4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

        currentShader.setUniformMatrix4f("modelViewMatrix", modelViewMatrix);
        currentShader.setUniformMatrix4f("projectionMatrix", projectionMatrix);
        currentShader.setUniformMatrix4f("modelViewProjectionMatrix", modelViewProjectionMatrix);

        // Dessiner le plane
        ofPushMatrix();
        if (currentMappingMethod == NORMAL)
        {
            vboMesh.draw();
        }
        else
        {
            plane.draw();
        }
        ofPopMatrix();

        currentShader.end();
    }

    camera.end();

    ImGui::Begin("Mapping Options");
    const char *mappingOptions[] = {"diffuse", "displacement", "normal"};
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

    if (ImGui::TreeNode("Lighting Settings"))
    {
        // Position de la lumière
        float lightPos[3] = {lightPosition.x, lightPosition.y, lightPosition.z};
        if (ImGui::SliderFloat3("Light Position", lightPos, -300.0f, 300.0f))
        {
            lightPosition = glm::vec3(lightPos[0], lightPos[1], lightPos[2]);
        }

        // Couleur de la lumière
        float color[3] = {lightColor.x, lightColor.y, lightColor.z};
        if (ImGui::ColorEdit3("Light Color", color))
        {
            lightColor = glm::vec3(color[0], color[1], color[2]);
        }

        ImGui::TreePop();
    }

    ImGui::End();
}
