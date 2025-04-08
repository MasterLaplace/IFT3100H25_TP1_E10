#include "Coons.hpp"

namespace plugin::topology {

/*
    On instancie la courbe parametrique de Coons avec uniquement 4 points.
    On initialise les quatres courbes de Bezier a partir des points passes en parametre.
    Les points de controle intermediaires sont cree automatiquement au milieu de la courbe.
    Ce qui donne, au final, 4 lignes droites.

    Le premier point passe en parametre est celui en haut a gauche de la surface.
    Les autres sont passes dans le sens horaire.

    Par contre, le constructeur s'occupe de construire la surface selon la formule
    de la 202 des notes de cours : C1(0) = C3(0), C1(1) = C4(0), C2(0) = C3(1), C2(1) = C4(1)
*/

Coons::Coons(ofPoint c1, ofPoint c2, ofPoint c3, ofPoint c4)
    : curve1(c1, (c1 + c2) / 2.0f, c2), curve2(c4, (c4 + c3) / 2.0f, c3), curve3(c1, (c1 + c4) / 2.0f, c4),
      curve4(c2, (c2 + c3) / 2.0f, c3)
{
    updatePoints();
}

/*
    Retourne un seul point à l'index selectionne.
*/
const ofPoint Coons::getPoint(int index) const { return points[index]; }

/*
    Retourne le point selectionne.
    Si aucun point n'est selectionne, on retourne un point (-1, -1, -1).
*/
const ofPoint Coons::getPoint() const
{
    if (selectedPoint == -1)
    {
        return ofPoint{-1, -1, -1};
    }

    else
    {
        return points[selectedPoint];
    }
}

/*
    Retourne un vecteur qui contient tous les points.
*/
const std::vector<ofPoint> Coons::getPoints() const { return points; }

/*
    Permet de changer un point de la surface parametrique.
    ofPoint p est le nouveau point qu'on veut appliquer.
    int index est la position du point dans la liste de point.
*/
void Coons::setPoint(ofPoint p, int index)
{
    switch (index)
    {
    case 0: // Point partage entre la courbe 1 et 3.
        curve1.setC1(p);
        curve3.setC1(p);
        break;
    case 1: curve1.setC2(p); break;
    case 2: // Point partage entre la courbe 1 et 4.
        curve1.setC3(p);
        curve4.setC1(p);
        break;
    case 3: // Point partage entre la courbe 2 et 3.
        curve2.setC1(p);
        curve3.setC3(p);
        break;
    case 4: curve2.setC2(p); break;
    case 5: // Point partage entre la courbe 2 et 4.
        curve2.setC3(p);
        curve4.setC3(p);
        break;
    case 6: curve3.setC2(p); break;
    case 7: curve4.setC2(p); break;
    default:
        std::cerr << "Erreur : Conns::setPoint(ofPoint p, int index) -> index de point invalide (" << index << ")."
                  << std::endl;
        break;
    }
    updatePoints();
}

void Coons::setPoint(ofPoint p) { setPoint(p, selectedPoint); }

void Coons::setSelectedPoint(int index) { selectedPoint = index; }

/*
    Permet de changer tous les points en meme temps.
    vector<ofPoint> p doit etre un vecteur de 8 points.
    Le premier point est en haut a gauche et on tourne dans le sens horaire.
*/
void Coons::setPoints(std::vector<ofPoint> p)
{
    if (p.size() == 8)
    {
        points = p;
        updateCurves();
    }
    else
    {
        std::cerr << "Erreur : le nombre de point doit etre egale a 8." << std::endl;
    }
}

// Permet de dessiner la surface parametrique.
void Coons::draw()
{
    ofSetColor(0);
    ofSetLineWidth(2);

    int precision = 100; // Plus de point donne une courbe plus precise.

    // On dessine la surface parametrique
    for (int i = 0; i < precision; i++)
    {
        float u = static_cast<float>(i) / precision;
        for (int j = 0; j < precision; j++)
        {
            float v = static_cast<float>(j) / precision;
            ofPoint p1 = surfaceCoons(u, v);
            ofPoint p2 = surfaceCoons(u, static_cast<float>(j + 1) / precision);
            ofPoint p3 = surfaceCoons(static_cast<float>(i + 1) / precision, v);
            ofDrawLine(p1, p2);
            ofDrawLine(p1, p3);
        }
    }

    // On dessine les deux courbes de bezier pour fermer correctement la surface.
    curve2.draw(precision);
    curve4.draw(precision);

    // On dessine les point de controle.
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

/*
    Fonction d'interpolation bilineaire.
    Formule de la page 202 des notes de cours.
    blerp(u, v) = (1−u)(1−v) C1(0)+ u (1−v) C1(1)+(1−u) v C2(0)+ u v C2(1)
*/
ofPoint Coons::blerp(float u, float v)
{
    ofPoint C1_0 = curve1.nlerpPoint(0.0f);
    ofPoint C1_1 = curve1.nlerpPoint(1.0f);
    ofPoint C2_0 = curve2.nlerpPoint(0.0f);
    ofPoint C2_1 = curve2.nlerpPoint(1.0f);

    ofPoint p = (1 - u) * (1 - v) * C1_0 + u * (1 - v) * C1_1 + (1 - u) * v * C2_0 + u * v * C2_1;

    return p;
}

/*
    Fonction d'interpolation lineaire entre les courbes 1 et 2.
    Formule de la page 202 des notes de cours.
    lerpu(u, v) = (1 − v) C1(u) + v C2(u)
*/
ofPoint Coons::lerpu(float u, float v)
{
    ofPoint p1 = curve1.nlerpPoint(u);
    ofPoint p2 = curve2.nlerpPoint(u);
    return (1 - v) * p1 + v * p2;
}

/*
    Fonction d'interpolation lineaire entre les courbes 3 et 4.
    Formule de la page 202 des notes de cours.
    lerpv(u, v) = (1 − u) C3(v) + u C4(v)
*/
ofPoint Coons::lerpv(float u, float v)
{
    ofPoint p1 = curve3.nlerpPoint(v);
    ofPoint p2 = curve4.nlerpPoint(v);
    return (1 - u) * p1 + u * p2;
}

/*
    Fonction pour calculer la surface de Coons.
    Formule de la page 202 des notes de cours.
    SurfaceCoons(u, v) = lerpu(u, v) + lerpv(u, v) − blerp(u, v)
*/
ofPoint Coons::surfaceCoons(float u, float v) { return lerpu(u, v) + lerpv(u, v) - blerp(u, v); }

/*
    Cette fonction met à jour les points de la courbe de Coons.
    Elle récupère les points de chaque courbe de Bezier et les ajoute au vecteur de points.
*/
void Coons::updatePoints()
{
    points.clear();

    std::array<ofPoint, 3> p = curve1.getPoints();
    for (int i = 0; i < p.size(); i++)
    {
        points.push_back(p[i]);
    }

    p = curve2.getPoints();
    for (int i = 0; i < p.size(); i++)
    {
        points.push_back(p[i]);
    }

    p = curve3.getPoints();
    points.push_back(p[1]);

    p = curve4.getPoints();
    points.push_back(p[1]);
}

/*
    Cette fonction met a jour les points des courbes de Bezier.
*/
void Coons::updateCurves()
{
    std::array<ofPoint, 3> c1 = {points[0], points[1], points[2]};
    std::array<ofPoint, 3> c2 = {points[3], points[4], points[5]};
    std::array<ofPoint, 3> c3 = {points[0], points[6], points[3]};
    std::array<ofPoint, 3> c4 = {points[2], points[7], points[5]};

    curve1.setPoints(c1);
    curve2.setPoints(c2);
    curve3.setPoints(c3);
    curve4.setPoints(c4);
}
} // namespace plugin::topology
