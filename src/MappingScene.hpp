#pragma once

#include "glm/glm.hpp"
#include "ofMain.h"
#include "ofxImGui.h"

enum MappingMethod {
    DIFFUSE,
    DISPLACEMENT,
    NORMAL
};

class MappingScene : public ofBaseApp {
public:
    void setup();
    void draw();
    void calculateTangents();

    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
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
    glm::vec3 lightPosition;
    glm::vec3 lightColor;
    float ambientStrength;
};
