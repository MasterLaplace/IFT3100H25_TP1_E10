#include "Importing.hpp"

namespace plugin::image::Importing {

std::optional<ofImage> importImage()
{
    ofFileDialogResult result = ofSystemLoadDialog("Importer l'image");

    if (!result.bSuccess)
        return std::nullopt;

    ofImage newImage;

    return newImage.load(result.getPath()) ? std::make_optional(newImage) : std::nullopt;
}

} // namespace plugin::image::Importing
