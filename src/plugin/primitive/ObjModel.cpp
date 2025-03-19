#include "ObjModel.hpp"
#include "../image/ResourceManager.hpp"

namespace plugin::primitive {

ObjModel::ObjModel(PrimitiveParams params) : Primitive(params){};

ObjModel::ObjModel(PrimitiveParams params, const std::shared_ptr<plugin::primitive::ObjModel> &other)
    : Primitive(params)
{
    _yourModel = other->getModel();
    _bbox = other->_bbox;
};

bool ObjModel::load(const std::string &path)
{
    bool result = _yourModel.load(path);

    if (result)
        _bbox.load(_yourModel.getMeshHelper(0));

    return result;
}

void ObjModel::draw()
{
    ofPushMatrix();
    ofTranslate(param.position);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y, param.scale.z);

    if (param.drawGizmo)
        _bbox.draw();

    ofSetColor(param.fillColor);
    ofSetLineWidth(param.outlineWidth);
    ofFill();

    if (param.isFilled)
        _yourModel.draw(OF_MESH_FILL);
    else
        _yourModel.draw(OF_MESH_WIREFRAME);

    ofPopMatrix();
}

bool ObjModel::isInside(const glm::vec3 &point) { return false; }

int ObjModel::getNumVertices() { return _yourModel.getMesh(0).getNumVertices(); }

int ObjModel::getNumFaces() { return _yourModel.getMesh(0).getNumIndices() / 3; }

} // namespace plugin::primitive
