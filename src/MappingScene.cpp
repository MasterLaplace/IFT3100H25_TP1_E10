#include "MappingScene.hpp"

void MappingScene::setup()
{
    ofSetFrameRate(60);
    ofEnableDepthTest();

    // Set up plane geometry
    plane.set(400, 400, 10, 10);
    plane.setPosition(0, 0, 0);

    // Set up camera
    camera.setDistance(600);
    camera.setNearClip(10);
    camera.setFarClip(2000);

    rotation = ofQuaternion(0, 0, 0, 1);
    currentRotation = ofQuaternion(0, 0, 0, 1);
    dragging = false;

    // Load textures
    diffuseTexture.load("diffuse.jpg");
    normalTexture.load("normal.jpg");

    // Load shader for normal mapping
    displacementShader.load("normal_mapping_330_vs.glsl", "normal_mapping_330_fs.glsl");

    // Set initial light position
    lightPos = ofVec3f(300, 300, 500);
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

    // Draw light source
    ofSetColor(255, 255, 0);
    ofDrawSphere(lightPos, 20);

    // Draw grid
    ofSetColor(100);
    ofDrawGrid(100, 10, false, false, true, false);

    // Apply object rotation
    ofPushMatrix();
    ofVec3f axis;
    float angle;
    currentRotation.getRotate(angle, axis);
    ofRotateDeg(angle, axis.x, axis.y, axis.z);

    // Use shader and draw plane
    if (displacementShader.isLoaded())
    {
        displacementShader.begin();
        displacementShader.setUniformTexture("diffuse", diffuseTexture.getTexture(), 0);
        plane.draw();
        displacementShader.end();
    }

    ofPopMatrix();
    camera.end();
}


void MappingScene::mousePressed(int x, int y, int button)
{
    if (button == OF_MOUSE_BUTTON_LEFT)
    {
        lastMouse = ofVec2f(x, y);
        dragging = true;
    }
}

void MappingScene::mouseDragged(int x, int y, int button)
{
    if (dragging)
    {
        float rotX = (x - lastMouse.x) * 0.5;
        float rotY = (y - lastMouse.y) * 0.5;
        ofQuaternion yRot(rotX, ofVec3f(0, 1, 0));
        ofQuaternion xRot(rotY, ofVec3f(1, 0, 0));
        rotation = yRot * xRot;
        currentRotation = rotation * currentRotation;
        lastMouse = ofVec2f(x, y);
    }
}

void MappingScene::mouseReleased(int x, int y, int button) { dragging = false; }
