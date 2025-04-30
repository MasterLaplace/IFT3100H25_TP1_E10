#include "PBRScene.hpp"

void PBRScene::setup()
{
    ofDisableArbTex();
    centerSphere.set(5, 5);
    centerSphere.setPosition(0, 0, 0);

    cam.setPosition(0, 0, -500);
    cam.lookAt({0, 0, 0});

    pointLightShader.load("shaders/pbr/point");

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
    light.color = ofColor(255, 255, 255);
    light.type = POINT;
    light.direction = {1, 0, 0};
    lights.push_back(light);
}

void PBRScene::setupPointLightShader(int primitiveIndex, int lightIndex)
{
    PBRPrimitive &p = primitives[primitiveIndex];

    pointLightShader.begin();

    pointLightShader.setUniform3f("material_color_ambient", p.ambiantColor.x / 255.0f, p.ambiantColor.y / 255.0f,
                                  p.ambiantColor.z / 255.0f);
    pointLightShader.setUniform3f("material_color_diffuse", 1.0f, 1.0f, 1.0f);  // diffuse tint
    pointLightShader.setUniform3f("material_color_specular", 1.0f, 1.0f, 1.0f); // specular tint
    pointLightShader.setUniform1f("material_brightness", p.brightness);
    pointLightShader.setUniform1f("material_metallic", p.metallic);
    pointLightShader.setUniform1f("material_roughness", p.roughness);
    pointLightShader.setUniform1f("material_occlusion", p.occlusion);
    pointLightShader.setUniform3f("material_fresnel_ior", 0.0f, 0.0f, 0.0f); // fresnel ior
    pointLightShader.setUniform1f("tone_mapping_exposure", 1.0f);
    pointLightShader.setUniform1f("tone_mapping_gamma", 2.0f);
    pointLightShader.setUniform1i("tone_mapping_toggle", true);

    pointLightShader.setUniform3f("light_position", lights[0].position);
    pointLightShader.setUniform3f("light_color", lights[0].color.r / 255.0f, lights[0].color.g / 255.0f,
                                  lights[0].color.b / 255.0f);
    pointLightShader.setUniform1f("light_intensity", 1.0f);

    pointLightShader.setUniform3f("camera_position", cam.getGlobalPosition());

    pointLightShader.setUniformTexture(
        "texture_diffuse", p.diffuseTexture.isAllocated() ? p.diffuseTexture.getTexture() : whiteTexture, 0);
    pointLightShader.setUniformTexture(
        "texture_metallic", p.metallicTexture.isAllocated() ? p.metallicTexture.getTexture() : whiteTexture, 1);
    pointLightShader.setUniformTexture(
        "texture_roughness", p.roughnessTexture.isAllocated() ? p.roughnessTexture.getTexture() : whiteTexture, 2);
    pointLightShader.setUniformTexture(
        "texture_occlusion", p.occlusionTexture.isAllocated() ? p.occlusionTexture.getTexture() : whiteTexture, 3);

    ofMatrix4x4 modelViewMatrix = cam.getModelViewMatrix();
    ofMatrix4x4 projectionMatrix = cam.getProjectionMatrix();

    pointLightShader.setUniformMatrix4f("modelViewMatrix", modelViewMatrix);
    pointLightShader.setUniformMatrix4f("projectionMatrix", projectionMatrix);

    pointLightShader.end();
}

void PBRScene::setupDirectionalLightShader(int primitiveIndex, int lightIndex) {}

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

    ofDrawAxis(100);

    // on dessine le curseur
    ofSetColor(100, 150, 77);
    ofPushMatrix();
    ofTranslate(centerPosition);
    centerSphere.draw();
    ofPopMatrix();

    for (size_t i = 0; i < primitives.size(); ++i)
    {
        setupPointLightShader(i, 0);
        pointLightShader.begin();
        ofSetColor(255, 255, 255);
        ofPushMatrix();
        ofTranslate(primitives[i].position);
        ofRotateXDeg(primitives[i].rotation.x);
        ofRotateYDeg(primitives[i].rotation.y);
        ofRotateZDeg(primitives[i].rotation.z);
        ofScale(primitives[i].scale);
        primitives[i].primitive.draw();

        // si la primitive est sélectionnée, on dessine le wireframe
        if (i == selectedPrimitiveIndex)
        {
            ofSetColor(255, 0, 0);
            primitives[i].primitive.drawWireframe();
        }
        ofPopMatrix();
        pointLightShader.end();
    }

    for (size_t i = 0; i < lights.size(); ++i)
    {
        ofPushMatrix();
        ofTranslate(lights[i].position);

        // indicateur de la position de la lumiere
        ofSetColor(lights[i].color);
        ofDrawSphere(5);
        ofSetColor(lights[i].color.r, lights[i].color.g, lights[i].color.b, 127);
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

        // si la lumiere est sélectionnée, on dessine un indicateur
        if (i == selectedLightIndex)
        {
            ofSetColor(255, 0, 0);
            ofDrawLine(-10, 0, 0, 10, 0, 0);
            ofDrawLine(0, -10, 0, 0, 10, 0);
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
    if (ImGui::Button("Add Sphere"))
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

    if (ImGui::Button("Add Box"))
    {
        PBRPrimitive box;
        box.name = "Box " + ofToString(nextPrimitiveId++);
        box.primitive = ofBoxPrimitive(100, 100, 100);
        box.position = centerPosition;
        box.rotation = {0, 0, 0};
        box.scale = {1, 1, 1};
        primitives.push_back(box);
        setupBaseMat(nextPrimitiveId - 1);
    }

    if (ImGui::ListBoxHeader(""))
    {
        for (int i = 0; i < primitives.size(); ++i)
        {
            const bool isSelected = (i == selectedPrimitiveIndex);
            if (ImGui::Selectable(primitives[i].name.c_str(), isSelected))
            {
                selectedPrimitiveIndex = i;
            }
        }
        ImGui::ListBoxFooter();
    }

    if (selectedPrimitiveIndex >= 0)
    {
        PBRPrimitive &p = primitives[selectedPrimitiveIndex];

        ImGui::Text("Edition: %s", p.name.c_str());
        ImGui::DragFloat3("Position", &p.position.x, 1.0f);
        ImGui::DragFloat3("Rotation", &p.rotation.x, 1.0f);
        ImGui::DragFloat3("Echelle", &p.scale.x, 0.01f, 0.01f, 10.0f);
        ImGui::Separator();

        ImGui::Text("Propriétés du matériau");
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
    }

    ImGui::End();

    // fenetre pour le curseur
    ImGui::SetNextWindowPos(ImVec2(10, 350), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 50), ImGuiCond_Once);
    ImGui::Begin("Curseur");
    ImGui::DragFloat3("Position", &centerPosition.x, 1.0f);
    ImGui::End();

    // fenetre pour la gestion des lumières
    ImGui::SetNextWindowPos(ImVec2(10, 430), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Once);
    ImGui::Begin("Illumination");
    if (ImGui::Button("Ajouter ponctuelle"))
    {
        PBRLight light;
        light.name = "Ponctuelle " + ofToString(nextLightId++);
        light.position = centerPosition;
        light.color = ofColor(255, 255, 255);
        light.type = POINT;
        light.direction = {1, 0, 0};
        lights.push_back(light);
    }

    if (ImGui::Button("Ajouter directionnelle"))
    {
        PBRLight light;
        light.name = "Directionnelle " + ofToString(nextLightId++);
        light.position = centerPosition;
        light.color = ofColor(255, 255, 255);
        light.type = DIRECTIONAL;
        light.direction = {1, 0, 0};
        lights.push_back(light);
    }

    if (ImGui::ListBoxHeader(""))
    {
        for (int i = 0; i < lights.size(); ++i)
        {
            const bool isSelected = (i == selectedLightIndex);

            if (ImGui::Selectable(lights[i].name.c_str(), isSelected))
            {
                selectedLightIndex = i;
            }
        }
        ImGui::ListBoxFooter();
    }

    if (selectedLightIndex >= 0)
    {
        PBRLight &l = lights[selectedLightIndex];
        ImGui::Text("Edition: %d", selectedLightIndex);
        ImGui::DragFloat3("Position", &l.position.x, 1.0f);

        ofVec3f color = {l.color.r / 255.0f, l.color.g / 255.0f, l.color.b / 255.0f};
        if (ImGui::ColorEdit3("Couleur", &color.x, ImGuiColorEditFlags_Float))
        {
            l.color = ofColor(color.x * 255, color.y * 255, color.z * 255);
        }
        if (l.type == DIRECTIONAL)
        {
            ImGui::DragFloat3("Direction", &l.direction.x, 0.01f, -1.0f, 1.0f);
        }
    }
    ImGui::End();
}

void PBRScene::setupBaseMat(int i)
{
    PBRPrimitive &p = primitives[i];
    p.ambiantColor = {1, 1, 1};
    p.metallic = 0.0f;
    p.roughness = 0.5f;
    p.occlusion = 1.0f;
    p.brightness = 1.0f;
}
