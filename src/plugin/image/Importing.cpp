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

    auto model = std::make_shared<geometry::ObjModel>();

    if (model->load(result.getPath()))
    {
        return ResourceManager::instance()->addModel(model, result.getName());
    }
    return false;
}

} // namespace plugin::image::Importing
