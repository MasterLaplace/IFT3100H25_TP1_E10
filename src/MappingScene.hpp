#pragma once

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

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

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

    // Parallax parameters
    float heightScale;
    int numLayers;
    bool useParallax;

    // Light position
    ofVec3f lightPos;

    MappingMethod currentMappingMethod;
};
