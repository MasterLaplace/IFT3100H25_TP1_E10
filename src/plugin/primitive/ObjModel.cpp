#include "ObjModel.hpp"

namespace plugin::primitive {

ObjModel::ObjModel(PrimitiveParams params) : Primitive(params){};

ObjModel::ObjModel(PrimitiveParams params, const std::shared_ptr<plugin::primitive::ObjModel> &other) : Primitive(params)
{
    yourModel = other->getModel();
};

bool ObjModel::load(const std::string &path) { return yourModel.load(path); }

void ObjModel::draw()
{
    ofSetColor(param.fillColor);
    ofPushMatrix();
    ofTranslate(param.position);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y, param.scale.z);

    if (param.isFilled)
        yourModel.draw(OF_MESH_FILL);
    else
        yourModel.draw(OF_MESH_WIREFRAME);

    ofPopMatrix();
}

bool ObjModel::isInside(const glm::vec3 &point) { return false; }

int ObjModel::getNumVertices() { return yourModel.getMesh(0).getNumVertices(); }

int ObjModel::getNumFaces() { return yourModel.getMesh(0).getNumIndices() / 3; }

} // namespace plugin::primitive
