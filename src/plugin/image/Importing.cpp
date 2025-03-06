#include "Importing.hpp"
#include "ResourceManager.hpp"

namespace plugin::image::Importing {

bool importImage()
{
    ofFileDialogResult result = ofSystemLoadDialog("Importer l'image");

    if (!result.bSuccess)
        return false;

    auto image = std::make_shared<Image>();

    if (image->load(result.getPath()))
    {
        return ResourceManager::instance()->addImage(image, result.getName());
    }
    return false;
}

bool importModel()
{
    ofFileDialogResult result = ofSystemLoadDialog("Importer le modèle");

    if (!result.bSuccess)
        return false;

    primitive::PrimitiveParams params;
    params.position = glm::vec3(0.0f, 0.0f, 0.0f);
    params.fillColor = ofColor::white;
    params.outlineColor = ofColor::black;
    params.outlineWidth = 1;
    params.isFilled = true;

    auto model = std::make_shared<primitive::ObjModel>(params);

    if (model->load(result.getPath()))
    {
        return ResourceManager::instance()->addModel(model, result.getName());
    }
    return false;
}

} // namespace plugin::image::Importing
