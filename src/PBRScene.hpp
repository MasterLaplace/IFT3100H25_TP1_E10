#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "plugin/image/ResourceManager.hpp"
#include "plugin/texture/Skybox.hpp"

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
        ofImage normalTexture;
        ofImage heightTexture;

        ofVboMesh vboMesh;
    };

    enum LightType {
        DIRECTIONAL,
        POINT
    };

    struct PBRLight {
        string name;
        float intensity = 0.1f;
        ofVec3f position;
        ofVec3f color;
        LightType type;
        ofVec3f direction;
    };

public:
    void setup();
    void draw();

private:
    vector<PBRPrimitive> primitives;
    vector<PBRLight> lights;

    ofShader shader;
    ofTexture whiteTexture;
    ofFbo lightFbo;
    ofFbo finalFbo;

    int selectedPrimitiveIndex = -1;
    int selectedLightIndex = -1;
    string selectedSkyboxName = "";
    int nextPrimitiveId = 0;
    int nextLightId = 0;

    ofEasyCam cam;

    ofSpherePrimitive centerSphere;
    glm::vec3 centerPosition = {0, 0, 0};

    plugin::texture::Skybox skybox;
    bool showSkybox = true;

    void setupShader(int primitiveIndex, int lightIndex);
    void drawGui();
    void setupBaseMat(int i);
    void calculateTangents(int i);
};
