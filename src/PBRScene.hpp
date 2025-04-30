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
        float metallic = 0.0f;
        float roughness = 0.0f;
        float occlusion = 1.0f;
        float brightness = 1.0f;
        ofVec3f ambiantColor = {1, 1, 1};

        ofImage diffuseTexture;
        ofImage metallicTexture;
        ofImage roughnessTexture;
        ofImage occlusionTexture;
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

    ofShader pointLightShader;
    ofShader directionalLightShader;
    ofShader postProcessShader;
    ofTexture whiteTexture;
    ofFbo lightFbo;
    ofFbo finalFbo;

    int selectedPrimitiveIndex = -1;
    int selectedLightIndex = -1;
    int nextPrimitiveId = 0;
    int nextLightId = 0;

    ofEasyCam cam;

    ofSpherePrimitive centerSphere;
    glm::vec3 centerPosition = {0, 0, 0};

    void setupPointLightShader(int primitiveIndex, int lightIndex);
    void setupDirectionalLightShader(int primitiveIndex, int lightIndex);
    void drawGui();
    void setupBaseMat(int i);
};
