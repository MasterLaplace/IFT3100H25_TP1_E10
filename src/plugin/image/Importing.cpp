#include "Importing.hpp"
#include "ResourceManager.hpp"
#include "plugin/texture/texture.hpp"

using namespace plugin::texture;

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

bool importCubeMap()
{
    ofFileDialogResult result = ofSystemLoadDialog("Importer le cubemap");
    
    // On vérifie si l'utilisateur a bien sélectionné un fichier
    if (!result.bSuccess)
        return false;
    
    // On vérifie si l'image a bien été chargée
    ofImage crossImage;
    if (!crossImage.load(result.getPath()))
        return false;
    
    int width = crossImage.getWidth();
    int height = crossImage.getHeight();

    // Vérifie si l'image est bien au format croix (rapport 4:3)
    if (width / 4 != height / 3) {
        ofLogError() << "Format d'image non valide ! Elle doit être au format 4:3.";
        return false;
    }

    // On sépare l'image en 6 faces
    auto textures = std::make_shared<std::array<ofTexture, 6>>();
    int faceSize = crossImage.getWidth() / 4;

    std::vector<glm::vec2> facePositions = {
        {3, 1}, // Right
        {1, 1}, // Left
        {1, 0}, // Top
        {1, 2}, // Bottom
        {2, 1}, // Front
        {0, 1}  // Back
    };

    for (int i = 0; i < 6; i++) {
        ofPixels pixels;
        crossImage.getPixels().cropTo(pixels, facePositions[i].x * faceSize, facePositions[i].y * faceSize, faceSize, faceSize);
        textures->at(i).allocate(faceSize, faceSize, GL_RGB);
        textures->at(i).loadData(pixels);
    }
    
    // Without extension
    string name = result.getName();
    name = name.substr(0, name.find_last_of('.'));
    return ResourceManager::instance()->addCubeMap(textures, name);
}

} // namespace plugin::image::Importing
