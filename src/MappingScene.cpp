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

    ofLoadImage(diffuseTexture, "mapping/diffuse.jpg");
    ofLoadImage(normalTexture, "mapping/normal.jpg");
    ofLoadImage(heightMap, "mapping/height.jpg");
    plane.mapTexCoordsFromTexture(diffuseTexture);

    // Set initial light position
    lightPos = ofVec3f(300, 300, 500);

    // Initialize the mapping method
    currentMappingMethod = DIFFUSE;

   // Load default shader (diffuse)
    currentShader.load("mapping/diffuse/shader");
}

void MappingScene::update()
{
    // Update light position (simple animation)
    float time = ofGetElapsedTimef();
    lightPos.x = 300 * sin(time * 0.5);
    lightPos.z = 300 * cos(time * 0.5) + 500;
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

    // Draw light source
    ofSetColor(255, 255, 0);
    ofDrawSphere(lightPos, 20);

    ofSetColor(255); 
    // Use shader and draw plane
    if (currentShader.isLoaded())
    {
        currentShader.setUniformTexture("diffuseTexture", diffuseTexture, 0);

        switch (currentMappingMethod)
        {
        case DISPLACEMENT:
            currentShader.setUniformTexture("heightMap", heightMap, 1);
            break;
        case NORMAL:
            currentShader.setUniformTexture("normalTexture", normalTexture, 2);
            break;
        case PARALLAX:
            break;
        }

        currentShader.begin();

        ofPushMatrix();
        plane.draw();
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
    ImGui::End();
}

void MappingScene::mousePressed(int x, int y, int button)
{

}

void MappingScene::mouseDragged(int x, int y, int button)
{

}

void MappingScene::mouseReleased(int x, int y, int button) { dragging = false; }
