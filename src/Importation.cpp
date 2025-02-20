#include "Importation.hpp"

void Importation::setup() { }

void Importation::update()
{

}

// Affichage de l'image importée
void Importation::draw()
{
    ofSetColor(255); // Réinitialise la couleur de dessin à blanc
    for (auto &img : images)
    {
        // Calculer les coordonnées pour centrer l'image
        float x = (ofGetWidth() - img.getWidth()) / 2;
        float y = (ofGetHeight() - img.getHeight()) / 2;
        img.draw(x, y); // Dessine chaque image au centre de l'écran
    }
}

// Ouvrir le dialogue d'importation
void Importation::importImage()
{
    ofFileDialogResult result = ofSystemLoadDialog("Importer l'image");
    if (result.bSuccess)
    {
        ofImage newImage;
        if (newImage.load(result.getPath()))
        {
            images.push_back(newImage);
            imageLoaded = true;
        }
        else
        {
            ofLogError() << "Échec du chargement de l'image.";
        }
    }
}