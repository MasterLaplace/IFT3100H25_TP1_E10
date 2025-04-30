#pragma once
#include "ofMain.h"
#include "ofxImGui.h"

class PBRScene {
    struct PBRPrimitive {
        string name;
        of3dPrimitive primitive;
        ofVec3f position;
        ofVec3f rotation;
        ofVec3f scale;
    };

    enum LightType {
        DIRECTIONAL,
        POINT
    };

    struct PBRLight {
        string name;
        ofVec3f position;
        ofColor color;
        LightType type;
        ofVec3f direction;
    };

public:
    void setup();
    void draw();

private:
    vector<PBRPrimitive> primitives;
    vector<PBRLight> lights;

    int selectedPrimitiveIndex = -1;
    int selectedLightIndex = -1;
    int nextPrimitiveId = 0;
    int nextLightId = 0;

    ofEasyCam cam;

    ofSpherePrimitive centerSphere;
    glm::vec3 centerPosition = {0, 0, 0};

    void drawGui();
};