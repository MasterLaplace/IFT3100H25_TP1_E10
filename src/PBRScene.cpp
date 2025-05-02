#include "PBRScene.hpp"

void PBRScene::setup()
{
    ofDisableArbTex();
    centerSphere.set(5, 5);
    centerSphere.setPosition(0, 0, 0);

    cam.setPosition(0, 0, -500);
    cam.lookAt({0, 0, 0});

    shader.load("shaders/pbr/shader");

    ofPixels pixels;
    pixels.allocate(1, 1, OF_PIXELS_RGB);
    pixels.setColor(ofColor::white);
    ofImage whiteImage;
    whiteImage.setFromPixels(pixels);
    whiteTexture = whiteImage.getTexture();
    whiteTexture.setTextureWrap(GL_REPEAT, GL_REPEAT);

    PBRPrimitive sphere;
    sphere.name = "Sphere " + ofToString(nextPrimitiveId++);
    sphere.primitive = ofSpherePrimitive(50, 16);
    sphere.position = centerPosition;
    sphere.rotation = {0, 0, 0};
    sphere.scale = {1, 1, 1};
    primitives.push_back(sphere);
    setupBaseMat(nextPrimitiveId - 1);

    PBRLight light;
    light.name = "Ponctuelle " + ofToString(nextLightId++);
    light.position = {0, 400, 0};
    light.color = {1, 1, 1};
    light.type = POINT;
    light.direction = {1, 0, 0};
    lights.push_back(light);
}

void PBRScene::setupShader(int primitiveIndex, int lightIndex)
{
    PBRPrimitive &p = primitives[primitiveIndex];

    shader.begin();

    shader.setUniform3f("material_color_ambient", p.ambiantColor.x, p.ambiantColor.y, p.ambiantColor.z);
    shader.setUniform3f("material_color_diffuse", 1.0f, 1.0f, 1.0f);  // diffuse tint
    shader.setUniform3f("material_color_specular", 1.0f, 1.0f, 1.0f); // specular tint
    shader.setUniform1f("material_brightness", p.brightness);
    shader.setUniform1f("material_metallic", p.metallic);
    shader.setUniform1f("material_roughness", p.roughness);
    shader.setUniform1f("material_occlusion", p.occlusion);
    shader.setUniform3f("material_fresnel_ior", 0.0f, 0.0f, 0.0f); // fresnel ior
    shader.setUniform1f("tone_mapping_exposure", 1.0f);
    shader.setUniform1f("tone_mapping_gamma", 2.0f);
    shader.setUniform1i("tone_mapping_toggle", true);

    for (size_t i = 0; i < lights.size(); ++i)
    {
        std::string idx = "lights[" + std::to_string(i) + "]";
        shader.setUniform1i(idx + ".type", lights[i].type);
        shader.setUniform3f(idx + ".position", lights[i].position);
        shader.setUniform3f(idx + ".direction", lights[i].direction);
        shader.setUniform3f(idx + ".color", lights[i].color.x, lights[i].color.y, lights[i].color.z);
        shader.setUniform1f(idx + ".intensity", 1.0f);
    }
    shader.setUniform1i("light_count", lights.size());

    shader.setUniform3f("view_position", cam.getGlobalPosition());

    shader.setUniformTexture("texture_diffuse",
                             p.diffuseTexture.isAllocated() ? p.diffuseTexture.getTexture() : whiteTexture, 0);
    shader.setUniformTexture("texture_metallic",
                             p.metallicTexture.isAllocated() ? p.metallicTexture.getTexture() : whiteTexture, 1);
    shader.setUniformTexture("texture_roughness",
                             p.roughnessTexture.isAllocated() ? p.roughnessTexture.getTexture() : whiteTexture, 2);
    shader.setUniformTexture("texture_occlusion",
                             p.occlusionTexture.isAllocated() ? p.occlusionTexture.getTexture() : whiteTexture, 3);
    if (p.normalTexture.isAllocated())
    {
        shader.setUniformTexture("texture_normal", p.normalTexture.getTexture(), 4);
        shader.setUniform1i("use_normal_map", 1);
    }
    else
    {
        shader.setUniform1i("use_normal_map", 0);
    }

    if (p.heightTexture.isAllocated())
    {
        shader.setUniformTexture("texture_height", p.heightTexture.getTexture(), 5);
        shader.setUniform1i("use_height_map", 1);
    }
    else
    {
        shader.setUniform1i("use_height_map", 0);
    }

    ofMatrix4x4 modelMatrix = p.primitive.getGlobalTransformMatrix();
    ofMatrix4x4 modelViewMatrix = cam.getModelViewMatrix();
    ofMatrix4x4 projectionMatrix = cam.getProjectionMatrix();

    shader.setUniformMatrix4f("modelMatrix", modelMatrix);
    shader.setUniformMatrix4f("modelViewMatrix", modelViewMatrix);
    shader.setUniformMatrix4f("projectionMatrix", projectionMatrix);

    shader.end();
}

void PBRScene::draw()
{
    if (ImGui::GetIO().WantCaptureMouse)
    {
        cam.disableMouseInput();
    }
    else
    {
        cam.enableMouseInput();
    }

    ofBackground(40);
    ofEnableDepthTest();
    cam.begin();

    // on dessine le skybox
    if (skybox.isSkyboxLoaded() && showSkybox)
    {
        skybox.draw(cam.getGlobalPosition());
    }

    ofDrawAxis(100);

    // on dessine le curseur
    ofSetColor(100, 150, 77);
    ofPushMatrix();
    ofTranslate(centerPosition);
    centerSphere.draw();
    ofPopMatrix();

    for (size_t i = 0; i < primitives.size(); ++i)
    {
        setupShader(i, 0);
        shader.begin();
        ofSetColor(255, 255, 255);
        ofPushMatrix();
        ofTranslate(primitives[i].position);
        ofRotateXDeg(primitives[i].rotation.x);
        ofRotateYDeg(primitives[i].rotation.y);
        ofRotateZDeg(primitives[i].rotation.z);
        ofScale(primitives[i].scale);
        primitives[i].vboMesh.draw();

        shader.end();

        // si la primitive est s�lectionn�e, on dessine le wireframe
        if (int(i) == selectedPrimitiveIndex)
        {
            ofSetColor(255, 0, 0);
            primitives[i].primitive.drawWireframe();
        }
        ofPopMatrix();
    }

    for (size_t i = 0; i < lights.size(); ++i)
    {
        ofPushMatrix();
        ofTranslate(lights[i].position);

        // indicateur de la position de la lumiere
        ofSetColor(lights[i].color.x * 255, lights[i].color.y * 255, lights[i].color.z * 255, 255);
        ofDrawSphere(5);
        ofSetColor(lights[i].color.x * 255, lights[i].color.y * 255, lights[i].color.z * 255, 127);
        ofDrawSphere(10);

        // si la lumiere est directionnelle, on dessine une fleche
        if (lights[i].type == DIRECTIONAL)
        {
            // calculer la rotation qui aligne le vecteur -Z avec la direction
            ofVec3f forward = ofVec3f(0, 0, -1);
            ofVec3f dir = lights[i].direction.getNormalized();
            ofQuaternion q;
            q.makeRotate(forward, dir);

            // appliquer la rotation
            ofMatrix4x4 mat;
            q.get(mat);
            ofMultMatrix(mat);
            ofDrawArrow(ofVec3f(0), ofVec3f(0, 0, -40), 5); // vers -Z en local
        }

        // si la lumiere est s�lectionn�e, on dessine un indicateur
        if (int(i) == selectedLightIndex)
        {
            ofSetColor(255, 0, 0);
            ofDrawLine(-20, 0, 0, 20, 0, 0);
            ofDrawLine(0, -20, 0, 0, 20, 0);
        }
        ofPopMatrix();
    }

    cam.end();
    ofDisableDepthTest();

    drawGui();
}

void PBRScene::drawGui()
{
    ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    ImGui::Begin("Primitives");
    if (ImGui::Button("Ajouter Sphere"))
    {
        PBRPrimitive sphere;
        sphere.name = "Sphere " + ofToString(nextPrimitiveId++);
        sphere.primitive = ofSpherePrimitive(50, 16);
        sphere.position = centerPosition;
        sphere.rotation = {0, 0, 0};
        sphere.scale = {1, 1, 1};
        primitives.push_back(sphere);
        setupBaseMat(nextPrimitiveId - 1);
    }

    if (ImGui::Button("Ajouter Boite"))
    {
        PBRPrimitive box;
        box.name = "Boite " + ofToString(nextPrimitiveId++);
        box.primitive = ofBoxPrimitive(100, 100, 100);
        box.position = centerPosition;
        box.rotation = {0, 0, 0};
        box.scale = {1, 1, 1};
        primitives.push_back(box);
        setupBaseMat(nextPrimitiveId - 1);
    }

    if (ImGui::BeginListBox(""))
    {
        for (int i = 0; i < int(primitives.size()); ++i)
        {
            const bool isSelected = (i == selectedPrimitiveIndex);
            if (ImGui::Selectable(primitives[i].name.c_str(), isSelected))
            {
                selectedPrimitiveIndex = i;
            }
        }
        ImGui::EndListBox();
    }

    if (selectedPrimitiveIndex >= 0)
    {
        if (ImGui::Button("Deselectionner##primitive"))
        {
            selectedPrimitiveIndex = -1;
        }
    }

    if (selectedPrimitiveIndex >= 0)
    {
        PBRPrimitive &p = primitives[selectedPrimitiveIndex];

        ImGui::Text("Edition: %s", p.name.c_str());
        ImGui::DragFloat3("Position", &p.position.x, 1.0f);
        ImGui::DragFloat3("Rotation", &p.rotation.x, 1.0f);
        ImGui::DragFloat3("Echelle", &p.scale.x, 0.01f, 0.01f, 10.0f);
        ImGui::Separator();

        ImGui::Text("Proprietes du materiau");
        ImGui::DragFloat("Brillance", &p.brightness, 0.01f, 0.0f, 10.0f);
        ImGui::DragFloat("Metallique", &p.metallic, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Rugosite", &p.roughness, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Occlusion", &p.occlusion, 0.01f, 0.0f, 1.0f);
        ImGui::ColorEdit3("Couleur ambiante", &p.ambiantColor.x, ImGuiColorEditFlags_Float);

        ImGui::Separator();
        ImGui::Text("Textures");
        ImGui::Text("Diffuse");
        ImGui::SameLine();
        if (ImGui::Button("Charger##diffuse"))
        {
            ofFileDialogResult result = ofSystemLoadDialog("Charger une texture diffuse");
            if (result.bSuccess)
            {
                p.diffuseTexture.load(result.getPath());
                p.diffuseTexture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
                p.primitive.mapTexCoordsFromTexture(p.diffuseTexture.getTexture());
            }
        }
        ImGui::SameLine();
        if (p.diffuseTexture.isAllocated())
        {
            ImGui::Text("Chargee");
        }
        else
        {
            ImGui::Text("Non Chargee");
        }

        ImGui::Text("Metallic");
        ImGui::SameLine();
        if (ImGui::Button("Charger##metallic"))
        {
            ofFileDialogResult result = ofSystemLoadDialog("Charger une texture metallique");
            if (result.bSuccess)
            {
                p.metallicTexture.load(result.getPath());
                p.metallicTexture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
                p.primitive.mapTexCoordsFromTexture(p.metallicTexture.getTexture());
            }
        }
        ImGui::SameLine();
        if (p.metallicTexture.isAllocated())
        {
            ImGui::Text("Chargee");
        }
        else
        {
            ImGui::Text("Non Chargee");
        }

        ImGui::Text("Roughness");
        ImGui::SameLine();
        if (ImGui::Button("Charger##roughness"))
        {
            ofFileDialogResult result = ofSystemLoadDialog("Charger une texture rugosite");
            if (result.bSuccess)
            {
                p.roughnessTexture.load(result.getPath());
                p.roughnessTexture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
                p.primitive.mapTexCoordsFromTexture(p.roughnessTexture.getTexture());
            }
        }
        ImGui::SameLine();
        if (p.roughnessTexture.isAllocated())
        {
            ImGui::Text("Chargee");
        }
        else
        {
            ImGui::Text("Non Chargee");
        }

        ImGui::Text("Occlusion");
        ImGui::SameLine();
        if (ImGui::Button("Charger##occlusion"))
        {
            ofFileDialogResult result = ofSystemLoadDialog("Charger une texture occlusion");
            if (result.bSuccess)
            {
                p.occlusionTexture.load(result.getPath());
                p.occlusionTexture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
                p.primitive.mapTexCoordsFromTexture(p.occlusionTexture.getTexture());
            }
        }
        ImGui::SameLine();
        if (p.occlusionTexture.isAllocated())
        {
            ImGui::Text("Chargee");
        }
        else
        {
            ImGui::Text("Non Chargee");
        }

        ImGui::Text("Normale");
        ImGui::SameLine();
        if (ImGui::Button("Charger##normale"))
        {
            ofFileDialogResult result = ofSystemLoadDialog("Charger une texture normale");
            if (result.bSuccess)
            {
                p.normalTexture.load(result.getPath());
                p.normalTexture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
                p.primitive.mapTexCoordsFromTexture(p.normalTexture.getTexture());
            }
        }
        ImGui::SameLine();
        if (p.normalTexture.isAllocated())
        {
            ImGui::Text("Chargee");
        }
        else
        {
            ImGui::Text("Non Chargee");
        }

        // Je commente cette partie, car elle ne fonctionne pas avec les cubes.
        // ImGui::Text("Deplacement");
        // ImGui::SameLine();
        // if (ImGui::Button("Charger##deplacement"))
        //{
        //    ofFileDialogResult result = ofSystemLoadDialog("Charger une texture deplacement");
        //    if (result.bSuccess)
        //    {
        //        p.heightTexture.load(result.getPath());
        //        p.heightTexture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
        //        p.primitive.mapTexCoordsFromTexture(p.heightTexture.getTexture());
        //    }
        //}
        // ImGui::SameLine();
        // if (p.heightTexture.isAllocated())
        //{
        //    ImGui::Text("Chargee");
        //}
        // else
        //{
        //    ImGui::Text("Non Chargee");
        //}
    }

    ImGui::End();

    // fenetre pour le curseur
    ImGui::SetNextWindowPos(ImVec2(10, 350), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 50), ImGuiCond_Once);
    ImGui::Begin("Curseur");
    ImGui::DragFloat3("Position", &centerPosition.x, 1.0f);
    ImGui::End();

    // fenetre pour la gestion des lumi�res
    ImGui::SetNextWindowPos(ImVec2(10, 430), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    ImGui::Begin("Illumination");
    if (ImGui::Button("Ajouter ponctuelle"))
    {
        PBRLight light;
        light.name = "Ponctuelle " + ofToString(nextLightId++);
        light.position = centerPosition;
        light.color = {1, 1, 1};
        light.type = POINT;
        light.direction = {1, 0, 0};
        lights.push_back(light);
    }

    if (ImGui::Button("Ajouter directionnelle"))
    {
        PBRLight light;
        light.name = "Directionnelle " + ofToString(nextLightId++);
        light.position = centerPosition;
        light.color = {1, 1, 1};
        light.type = DIRECTIONAL;
        light.direction = {1, 0, 0};
        lights.push_back(light);
    }

    if (ImGui::BeginListBox(""))
    {
        for (int i = 0; i < int(lights.size()); ++i)
        {
            const bool isSelected = (i == selectedLightIndex);

            if (ImGui::Selectable(lights[i].name.c_str(), isSelected))
            {
                selectedLightIndex = i;
            }
        }
        ImGui::EndListBox();
    }

    if (selectedLightIndex >= 0)
    {
        if (ImGui::Button("Deselectionner##lumiere"))
        {
            selectedLightIndex = -1;
        }
    }

    if (selectedLightIndex >= 0)
    {
        PBRLight &l = lights[selectedLightIndex];
        ImGui::Text("Edition: %d", selectedLightIndex);
        ImGui::DragFloat3("Position", &l.position.x, 1.0f);

        ImGui::ColorEdit3("Couleur", &l.color.x, ImGuiColorEditFlags_Float);

        if (l.type == DIRECTIONAL)
        {
            ImGui::DragFloat3("Direction", &l.direction.x, 0.01f, -1.0f, 1.0f);
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(10, 740), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 50), ImGuiCond_Once);
    ImGui::Begin("Skybox");
    if (ImGui::BeginListBox(""))
    {
        auto cubemaps = plugin::image::ResourceManager::instance()->getCubeMaps();
        for (auto &cubemap : cubemaps)
        {
            const bool isSelected = (cubemap.first == selectedSkyboxName);
            if (ImGui::Selectable(cubemap.first.c_str(), isSelected))
            {
                selectedSkyboxName = cubemap.first;
            }
        }
        ImGui::EndListBox();
    }

    if (selectedSkyboxName != "")
    {
        ImGui::Text("Skybox: %s", selectedSkyboxName.c_str());
        if (ImGui::Button("Charger##skybox"))
        {
            auto cubemaps = plugin::image::ResourceManager::instance()->getCubeMaps();
            if (cubemaps.find(selectedSkyboxName) != cubemaps.end())
            {
                skybox.load(selectedSkyboxName);
            }
        }
        if (ImGui::Button("Deselectionner##skybox"))
        {
            selectedSkyboxName = "";
        }
    }

    ImGui::Separator();
    ImGui::Text("Skybox chargee: %s", skybox.isSkyboxLoaded() ? "Oui" : "Non");
    if (skybox.isSkyboxLoaded())
    {
        ImGui::Checkbox("Afficher le skybox", &showSkybox);
        if (showSkybox)
        {
            ImGui::Text("Skybox visible");
        }
        else
        {
            ImGui::Text("Skybox invisible");
        }
    }
    ImGui::End();
}

void PBRScene::setupBaseMat(int i)
{
    PBRPrimitive &p = primitives[i];
    p.ambiantColor = {0.2, 0.5, 0.8};
    p.brightness = 0.180f;
    p.metallic = 0.780f;
    p.roughness = 0.410f;
    p.occlusion = 0.970f;

    calculateTangents(i);
}

void PBRScene::calculateTangents(int i)
{
    PBRPrimitive &p = primitives[i];

    // R�cup�rer les donn�es du mesh
    std::vector<glm::vec3> &vertices = p.primitive.getMesh().getVertices();
    std::vector<glm::vec3> &normals = p.primitive.getMesh().getNormals();
    std::vector<glm::vec2> &texCoords = p.primitive.getMesh().getTexCoords();
    std::vector<ofIndexType> indices = p.primitive.getMesh().getIndices();

    // Cr�er les vecteurs pour les tangentes et bitangentes
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

        // Calculer les diff�rences
        glm::vec3 deltaPos1 = v2 - v1;
        glm::vec3 deltaPos2 = v3 - v1;

        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        // Calculer la tangente et la bitangente
        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        if (std::isfinite(r))
        { // V�rifier que r n'est pas inf ou NaN
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

        // Orthogonaliser la tangente par rapport � la normale (Gram-Schmidt)
        t = (t - n * n.dot(t)).normalize();
    }

    p.vboMesh = p.primitive.getMesh();
    p.vboMesh.getVbo().setAttributeData(10, &tangents[0].x, 3, tangents.size(), GL_STATIC_DRAW);
}
