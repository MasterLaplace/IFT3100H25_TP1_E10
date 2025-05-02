#include "CatmullRom.hpp"

plugin::topology::CatmullRom::CatmullRom(ofPoint P1, ofPoint P2, ofPoint P3, ofPoint P4)
{
    points.push_back(P1);
    points.push_back(P2);
    points.push_back(P3);
    points.push_back(P4);
}

const ofPoint plugin::topology::CatmullRom::getPoint() const
{
    if (selectedPoint == -1)
    {
        return ofPoint{-1, -1, -1};
    }

    return points[selectedPoint];
}

const ofPoint plugin::topology::CatmullRom::getPoint(int index) const
{
    if (index < 0 || index >= int(points.size()))
    {
        std::cerr << "Erreur : CatmullRom::getPoint(int index) -> l'index est en dehors du vecteur points."
                  << std::endl;
        return ofPoint(-1, -1, -1);
    }

    return points[index];
}

const std::vector<ofPoint> plugin::topology::CatmullRom::getPoints() const { return points; }

const int plugin::topology::CatmullRom::getSelectedPoint() const { return selectedPoint; }

void plugin::topology::CatmullRom::setPoint(ofPoint p)
{
    if (selectedPoint < 0 || selectedPoint > int(points.size()) - 1)
    {
        std::cerr << "Erreur : CatmullRom::setPoint() -> selectedPoint est en dehors des limites du vecteur points."
                  << std::endl;
        return;
    }
    points[selectedPoint] = p;
}

void plugin::topology::CatmullRom::setPoints(std::vector<ofPoint> p)
{
    if (p.size() <= 3u)
    {
        std::cerr
            << "Erreur : CatmullRom::setPoints(std::vector<ofPoint> p) -> le vecteur p doit contenir au moins 4 points."
            << std::endl;
        return;
    }

    points = p;
}

void plugin::topology::CatmullRom::setSelectedPoint(int index)
{
    if (index < -1 || index > int(points.size()) - 1)
    {
        std::cerr << "Erreur : CatmullRom::setSelectedPoint() -> index est en dehors des limites du vecteur points."
                  << std::endl;
        return;
    }
    selectedPoint = index;
}

void plugin::topology::CatmullRom::draw() const
{
    // On dessine la courbe.
    ofSetColor(ofColor::black);

    // Cas special pour le premier segment.
    for (float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        ofPoint p0 = points[points.size() - 1]; // Le premier point est le dernier du vecteur.
        ofPoint p1 = points[0]; // C'est le premier point du vecteur, c'est lui qu'on traite dans ce cas special.
        ofPoint p2 = points[1];
        ofPoint p3 = points[2];

        // Calculer le point sur la courbe � l'aide de la fonction Catmull-Rom.
        ofPoint p = catmullRom(t, p0, p1, p2, p3);

        // Dessiner la courbe avec les points interpol�s.
        if (t > 0.0f)
        {
            ofPoint prevPoint = catmullRom(t - 0.01f, p0, p1, p2, p3);
            ofDrawLine(prevPoint, p);
        }
    }

    // Cas pour les segments intermediaires.
    for (int i = 1; i < points.size() - 2; ++i)
    {
        for (float t = 0.0f; t <= 1.0f; t += 0.01f)
        {
            ofPoint p0 = points[i - 1];
            ofPoint p1 = points[i]; // C'est le point qu'on traite actuellement
            ofPoint p2 = points[i + 1];
            ofPoint p3 = points[i + 2];

            // Calculer le point sur la courbe � l'aide de la fonction Catmull-Rom
            ofPoint p = catmullRom(t, p0, p1, p2, p3);

            // Dessiner la courbe avec les points interpol�s
            if (t > 0.0f)
            {
                ofPoint prevPoint = catmullRom(t - 0.01f, p0, p1, p2, p3);
                ofDrawLine(prevPoint, p);
            }
        }
    }

    // Cas special pour le dernier segment.
    for (float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        int n = points.size();
        ofPoint p0 = points[n - 3];
        ofPoint p1 = points[n - 2]; // C'est l'avant dernier point du vecteur. C'est celui qu'on traite en dernier.
        ofPoint p2 = points[n - 1];
        ofPoint p3 = points[0];

        // Calculer le point sur la courbe � l'aide de la fonction Catmull-Rom
        ofPoint p = catmullRom(t, p0, p1, p2, p3);

        // Dessiner la courbe avec les points interpol�s
        if (t > 0.0f)
        {
            ofPoint prevPoint = catmullRom(t - 0.01f, p0, p1, p2, p3);
            ofDrawLine(prevPoint, p);
        }
    }

    // On dessine les points de controle.
    for (int i = 0; i < points.size(); ++i)
    {
        if (i == selectedPoint)
        {
            ofSetColor(ofColor::green);
        }
        else
        {
            ofSetColor(ofColor::red);
        }
        ofDrawCircle(points[i], pointRadius);
    }
}

void plugin::topology::CatmullRom::addPoint()
{
    float x = ofGetWidth() / 2;
    float y = ofGetHeight() / 2;
    float z = 0.0f;

    ofPoint p(x, y, z);

    points.push_back(p);
}

ofPoint plugin::topology::CatmullRom::catmullRom(float t, const ofPoint &p0, const ofPoint &p1, const ofPoint &p2,
                                                 const ofPoint &p3) const
{
    float t2 = t * t;
    float t3 = t * t * t;

    // Formule de Catmull-Rom generee par ChatGPT.
    return 0.5 * ((2.0 * p1) + (-p0 + p2) * t + (2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3) * t2 +
                  (-p0 + 3.0 * p1 - 3.0 * p2 + p3) * t3);
}
