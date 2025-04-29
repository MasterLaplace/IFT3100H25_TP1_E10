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
    void draw();
    void calculateTangents();

    ofPlanePrimitive plane;
    ofVboMesh vboMesh;
    ofEasyCam camera;

    ofShader currentShader;
    ofTexture diffuseTexture;
    ofTexture normalTexture;
    ofTexture heightMap;

    MappingMethod currentMappingMethod;

    // Paramètres pour le déplacement
    float displacementScale;

    // Paramètres de la lumière
    glm::vec3 lightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.5f;
};
