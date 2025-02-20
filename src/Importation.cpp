#include "Importation.hpp"

void Importation::setup() { }

void Importation::update()
{

}

// Affichage de l'image import�e
void Importation::draw()
{
    ofSetColor(255); // R�initialise la couleur de dessin � blanc
    for (auto &img : images)
    {
        // Calculer les coordonn�es pour centrer l'image
        float x = (ofGetWidth() - img.getWidth()) / 2;
        float y = (ofGetHeight() - img.getHeight()) / 2;
        img.draw(x, y); // Dessine chaque image au centre de l'�cran
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
            ofLogError() << "�chec du chargement de l'image.";
        }
    }
}