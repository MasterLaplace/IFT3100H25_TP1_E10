#pragma once

#include "glm/glm.hpp"
#include "ofMain.h"
#include "ofxImGui.h"

enum MappingMethod {
    DIFFUSE,
    DISPLACEMENT,
    NORMAL,
    PARALLAX
};

class MappingScene : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // Primitive and camera
    ofPlanePrimitive plane;
    ofEasyCam camera;

    // Variables for rotation
    ofVec2f lastMouse;
    ofQuaternion rotation;
    ofQuaternion currentRotation;
    bool dragging;

    // Normal mapping variables
    ofShader currentShader;
    ofTexture diffuseTexture;
    ofTexture normalTexture;
    ofTexture heightMap;

    // Parameters for displacement shader
    float displacementScale = 0.0f; // Initialize to avoid undefined behavior

    MappingMethod currentMappingMethod;

    // Lighting parameters
    glm::vec3 lightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.5f;
};
