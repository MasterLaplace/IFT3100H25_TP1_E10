#include "Histogram.hpp"

namespace plugin::image {

// fonction d'initialisation
void Histogram::setup(ofImage _image)
{
    image = _image;
    font.load("arial.ttf", 26);

    // On calcule les histogrammes absolus et relatifs pour les trois couleurs.
    redAbsoluteHistogram = getRed();
    greenAbsoluteHistogram = getGreen();
    blueAbsoluteHistogram = getBlue();

    redRelativeHistogram = getRelativeHistogram(redAbsoluteHistogram);
    greenRelativeHistogram = getRelativeHistogram(greenAbsoluteHistogram);
    blueRelativeHistogram = getRelativeHistogram(blueAbsoluteHistogram);
}

// fonction de rendu
void Histogram::draw(char c)
{
    // On efface le canvas. Je ne suis meme pas certain que c'est reellement la bonne methode.
    ofClear(0);

    // On fait pointer les pointeurs vers les bons histogrammes.
    if (c == 'r')
    {
        histogramAbsolute = &redAbsoluteHistogram;
        histogramRelative = &redRelativeHistogram;
        color = ofColor::red;
    }
    else if (c == 'g')
    {
        histogramAbsolute = &greenAbsoluteHistogram;
        histogramRelative = &greenRelativeHistogram;
        color = ofColor::green;
    }
    else if (c == 'b')
    {
        histogramAbsolute = &blueAbsoluteHistogram;
        histogramRelative = &blueRelativeHistogram;
        color = ofColor::blue;
    }

    // On dessine l'histogramme relatif.
    drawHistogram();

    // On dessine les axes et le texte.
    drawXAxis();
    drawYAxis();

    // On dessine le tooltip.
    drawTooltip();
}

//--------------------------------------------------------------------------------------------------//
// Methode privees
//--------------------------------------------------------------------------------------------------//

/*
Brief : Permet de generer un histogramme absolu pour la couleur rouge.
Return : Un vecteur de 256 entiers representant l'histogramme.
*/

vector<int> Histogram::getRed()
{
    std::vector<int> red(MAX_COLOR_VALUE, 0);

    for (int i = 0; i < image.getWidth(); i++)
    {
        for (int j = 0; j < image.getHeight(); j++)
        {
            ofColor color = image.getColor(i, j);
            red[color.r]++;
        }
    }

    return red;
}

/*
Brief : Permet de generer un histogramme absolu pour la couleur verte.
Return : Un vecteur de 256 entiers representant l'histogramme.
*/

vector<int> Histogram::getGreen()
{
    std::vector<int> green(MAX_COLOR_VALUE, 0);

    for (int i = 0; i < image.getWidth(); i++)
    {
        for (int j = 0; j < image.getHeight(); j++)
        {
            ofColor color = image.getColor(i, j);
            green[color.g]++;
        }
    }

    return green;
}

/*
Brief : Permet de generer un histogramme absolu pour la couleur bleue.
Return : Un vecteur de 256 entiers representant l'histogramme.
*/

vector<int> Histogram::getBlue()
{
    std::vector<int> blue(MAX_COLOR_VALUE, 0);

    for (int i = 0; i < image.getWidth(); i++)
    {
        for (int j = 0; j < image.getHeight(); j++)
        {
            ofColor color = image.getColor(i, j);
            blue[color.b]++;
        }
    }

    return blue;
}

/*
Brief : Permet de generer un histogramme relatif a partir d'un histogramme absolu.
Return : Un vecteur de 256 float representant l'histogramme relatif.
*/

vector<float> Histogram::getRelativeHistogram(vector<int> h)
{
    vector<float> relativeHistogram(MAX_COLOR_VALUE, 0);
    maxValue = *max_element(h.begin(), h.end()); // Les valeurs de l'histogramme relatif sont calculees en fonction de
                                                 // la valeur maximale de l'histogramme absolu.

    for (int i = 0; i < h.size(); i++)
    {
        float result = (h[i] / static_cast<float>(maxValue)) * (MAX_Y - OFFSET * 2);
        relativeHistogram[i] = result;
    }

    return relativeHistogram;
}

/*
Brief : Permet de dessiner les barres verticales de l'histogramme relatif.
*/

void Histogram::drawHistogram()
{
    for (int i = 0; i < histogramRelative->size(); i++)
    {
        glm::vec2 barTop = glm::vec2(OFFSET + i * BAR_WIDTH, (MAX_Y - OFFSET) - (*histogramRelative)[i]);

        // Si la sourie survole une barre, on la colore en blanc.
        if (mouseIsHoveringBar(barTop, (*histogramRelative)[i]))
        {
            ofSetColor(ofColor::white);
        }
        else
        {
            ofSetColor(color);
        }

        ofDrawRectangle(barTop, BAR_WIDTH, (*histogramRelative)[i]);
    }
}

/*
Brief : Permet de dessiner l'axe des X avec son label.
*/

void Histogram::drawXAxis()
{
    ofSetColor(ofColor::white);

    // On dessine la grande ligne horizontale.
    glm::vec2 lineStart = glm::vec2(OFFSET, MAX_Y - OFFSET);
    glm::vec2 lineEnd = glm::vec2(MAX_X + OFFSET, MAX_Y - OFFSET);
    ofDrawLine(lineStart, lineEnd);

    // On dessine les petites lignes verticales.
    int nbrLines = MAX_COLOR_VALUE / 10;
    int spacing = MAX_X / nbrLines;

    glm::vec2 lineUp = glm::vec2(OFFSET + spacing, MAX_Y - OFFSET);
    glm::vec2 lineDown = glm::vec2(OFFSET + spacing, MAX_Y - OFFSET + 10);

    for (int i = 0; i < nbrLines; i++)
    {
        ofDrawLine(lineUp, lineDown);
        lineUp.x += spacing;
        lineDown.x += spacing;
    }

    // On dessine le label.
    std::string label = "Valeurs de couleur";
    float labelWidth = font.stringWidth(label);
    font.drawString(label, (ofGetWidth() - labelWidth) / 2, ofGetHeight() - OFFSET / 2);
}

/*
Brief : Permet de dessiner l'axe des Y avec son label.
*/

void Histogram::drawYAxis()
{
    ofSetColor(ofColor::white);

    // On dessine la grande ligne verticale.
    glm::vec2 lineStart = glm::vec2(OFFSET, MAX_Y - OFFSET);
    glm::vec2 lineEnd = glm::vec2(OFFSET, OFFSET);
    ofDrawLine(lineStart, lineEnd);

    // On dessine les petites lignes horizontales.
    int nbrLines = 4;
    int spacing = MAX_Y / nbrLines;

    glm::vec2 lineRight = glm::vec2(OFFSET, MAX_Y - OFFSET);
    glm::vec2 lineLeft = glm::vec2(OFFSET - 10, MAX_Y - OFFSET);

    for (int i = 0; i < nbrLines; i++)
    {
        ofDrawLine(lineRight, lineLeft);
        ofDrawBitmapString(ofToString(maxValue / nbrLines * i), OFFSET / 2, MAX_Y - OFFSET - spacing * i);
        lineRight.y -= spacing;
        lineLeft.y -= spacing;
    }

    // On dessine le label.
    std::string label = "Fréquence";
    drawVerticalText(label, (OFFSET / 2) - 10, ofGetHeight() / 2);
}

/*
Brief : Permet de dessiner du texte verticalement pour le label de l'axe des Y.
IMPORTANT : Cette methode est entierement ecrite par l'AI copilote.
*/
void Histogram::drawVerticalText(const std::string &text, float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotateDeg(-90);
    font.drawString(text, 0, 0);
    ofPopMatrix();
}

/*
Brief : Permet de verifier si la sourie survole une barre de l'histogramme.
Return : Un booleen qui indique si la sourie survole une barre.
*/

bool Histogram::mouseIsHoveringBar(glm::vec2 barTop, float barHeight)
{
    glm::vec2 mouse = glm::vec2(ofGetMouseX(), ofGetMouseY());
    bool isOverX = mouse.x > barTop.x && mouse.x < barTop.x + BAR_WIDTH;
    bool isOverY = mouse.y > barTop.y && mouse.y < barTop.y + barHeight;

    if (isOverX && isOverY)
    {
        return true;
    }

    return false;
}

/*
Brief : Permet de dessiner un tooltip lorsqu'on survole une barre de l'histogramme.
        On affiche la valeur de la couleur et sa frequence.
        Pour ce faire on utilise les valeurs de l'histogramme absolu.
*/

void Histogram::drawTooltip()
{
    for (int i = 0; i < histogramRelative->size(); i++)
    {
        float barHeight = (*histogramRelative)[i];
        int barTopX = OFFSET + i * BAR_WIDTH;
        int barTopY = (MAX_Y - OFFSET) - barHeight;
        glm::vec2 barTop = glm::vec2(barTopX, barTopY);

        if (mouseIsHoveringBar(barTop, barHeight))
        {
            std::string text =
                "Valeur de couleur: " + ofToString(i) + '\n' + "Frequence: " + ofToString((*histogramAbsolute)[i]);

            font.load("arial.ttf", 15);

            int textWidth = font.stringWidth(text);
            int textHeight = font.stringHeight(text);

            ofSetColor(ofColor::white);
            ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), textWidth, textHeight + 5);
            ofSetColor(ofColor::black);
            font.drawString(text, ofGetMouseX() + 10, ofGetMouseY() + 20);
        }
    }
}

} // namespace plugin::image
