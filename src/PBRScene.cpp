#include "PBRScene.hpp"

void PBRScene::setup()
{
    centerSphere.set(5, 5);
    centerSphere.setPosition(0, 0, 0);

    PBRPrimitive sphere;
    sphere.name = "Sphere " + ofToString(nextPrimitiveId++);
    sphere.primitive = ofSpherePrimitive(50, 16);
    sphere.position = centerPosition;
    sphere.rotation = {0, 0, 0};
    sphere.scale = {1, 1, 1};

    primitives.push_back(sphere);
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

    ofSetColor(100, 150, 77);
    ofPushMatrix();
    ofTranslate(centerPosition);
    centerSphere.draw();
    ofPopMatrix();

    for (size_t i = 0; i < primitives.size(); ++i)
    {

        ofSetColor(255, 255, 255);
        ofPushMatrix();
        ofTranslate(primitives[i].position);
        ofRotateXDeg(primitives[i].rotation.x);
        ofRotateYDeg(primitives[i].rotation.y);
        ofRotateZDeg(primitives[i].rotation.z);
        ofScale(primitives[i].scale);
        primitives[i].primitive.draw();

        if (i == selectedPrimitiveIndex)
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

        ofSetColor(lights[i].color);
        ofDrawSphere(5);

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
    ImGui::Begin("Primitives");
    ImGui::SetWindowSize(ImVec2(300, 600), ImGuiCond_Appearing);

    // Ajouter un bouton pour ajouter une boite, une sphere, etc.
    if (ImGui::Button("Add Sphere"))
    {
        PBRPrimitive sphere;
        sphere.name = "Sphere " + ofToString(nextPrimitiveId++);
        sphere.primitive = ofSpherePrimitive(50, 16);
        sphere.position = centerPosition;
        sphere.rotation = {0, 0, 0};
        sphere.scale = {1, 1, 1};
        primitives.push_back(sphere);
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
    }

    ImGui::End();

    ImGui::Begin("Curseur");
    // add a field to change the position of the center sphere
    ImGui::DragFloat3("Position", &centerPosition.x, 1.0f);

    ImGui::End();

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
        ImGui::DragFloat3("Direction", &l.direction.x, 0.01f, 0.0f, 1.0f);
    }

    ImGui::End();
}
