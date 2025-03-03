#include "Importing.hpp"

namespace plugin::image::Importing {

bool importImage(ofImage &image)
{
    ofFileDialogResult result = ofSystemLoadDialog("Importer l'image");

    if (!result.bSuccess)
        return false;

    return image.load(result.getPath());
}

bool importModel(geometry::ObjModels &model)
{
    ofFileDialogResult result = ofSystemLoadDialog("Importer le modèle");

    if (!result.bSuccess)
        return false;

    return model.load(result.getPath());
}

} // namespace plugin::image::Importing
