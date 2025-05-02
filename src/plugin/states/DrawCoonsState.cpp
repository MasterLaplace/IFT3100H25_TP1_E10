#include "DrawCoonsState.hpp"

plugin::states::DrawCoonsState::DrawCoonsState(curveType _type)
    : coons(ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f)),
      bezier(ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f)),
      catmull(ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f),
              ofPoint(0.0f, 0.0f, 0.0f))
{
    type = _type;
}

void plugin::states::DrawCoonsState::enter()
{
    ofBackground(255);
    ofSetColor(0);

    float w = ofGetWidth();
    float h = ofGetHeight();

    // On instancie Bezier
    ofPoint b1 = {100.0f, h / 2, 0.0f};
    ofPoint b2 = {w - 300.0f, h / 2, 0.0f};

    bezier.~BezierQuadratique();
    new (&bezier) plugin::topology::BezierQuadratique(b1, b2);

    // On instancie Catmull-Rom
    ofPoint cr1 = {100.0f, h / 2, 0.0f};
    ofPoint cr4 = {w - 300.0f, h / 2, 0.0f};
    ofPoint cr2 = cr1 + (cr4 - cr1) * (1.0f / 3.0f);
    ofPoint cr3 = cr1 + (cr4 - cr1) * (2.0f / 3.0f);

    catmull.~CatmullRom();
    new (&catmull) plugin::topology::CatmullRom(cr1, cr2, cr3, cr4);

    // On instancie Coons
    ofPoint c1 = {100.0f, 100.0f, 0.0f};         // Point en haut a gauche.
    ofPoint c2 = {w - 300.0f, 100.0f, 0.0f};     // Point en haut a droite.
    ofPoint c3 = {w - 300.0f, h - 100.0f, 0.0f}; // Point en bas a droite.
    ofPoint c4 = {100.0f, h - 100.0f, 0.0f};     // Point en bas a gauche.

    coons.~Coons();
    new (&coons) plugin::topology::Coons(c1, c2, c3, c4);

    windowResized(w, h);
}

void plugin::states::DrawCoonsState::update()
{
    if (isDragging)
    {
        ofPoint newPoint(mousePosition.x, mousePosition.y, selectedPoint.z);

        switch (type)
        {
        case plugin::states::BEZIER: bezier.setPoint(newPoint); break;
        case plugin::states::CATMULL_ROM: catmull.setPoint(newPoint); break;
        case plugin::states::COONS: coons.setPoint(newPoint); break;
        default: break;
        }
    }
}

void plugin::states::DrawCoonsState::draw()
{
    switch (type)
    {
    case plugin::states::BEZIER: bezier.drawWithPoints(100); break;
    case plugin::states::CATMULL_ROM: catmull.draw(); break;
    case plugin::states::COONS: coons.draw(); break;
    default: break;
    }
}

void plugin::states::DrawCoonsState::exit()
{
    bezier.~BezierQuadratique();
    catmull.~CatmullRom();
    coons.~Coons();
}

void plugin::states::DrawCoonsState::mouseDragged(int x, int y, int button)
{
    if (isDragging)
    {
        ofPoint newPoint(x, y, selectedPoint.z);

        switch (type)
        {
        case plugin::states::BEZIER: bezier.setPoint(newPoint); break;
        case plugin::states::CATMULL_ROM: catmull.setPoint(newPoint); break;
        case plugin::states::COONS: coons.setPoint(newPoint); break;
        default: break;
        }
    }
}

void plugin::states::DrawCoonsState::mousePressed(int x, int y, int button)
{
    switch (type)
    {
    case plugin::states::BEZIER:
        for (int i = 0; i < bezier.getPoints().size(); ++i)
        {
            if (isInside(bezier.getPoint(i)))
            {
                bezier.setSelectedPoint(i);
                selectedPoint = bezier.getPoint();
                isDragging = true;
                break;
            }

            bezier.setSelectedPoint(-1);
            isDragging = false;
        }
        break;

    case plugin::states::CATMULL_ROM:
        for (int i = 0; i < catmull.getPoints().size(); ++i)
        {
            if (isInside(catmull.getPoint(i)))
            {
                catmull.setSelectedPoint(i);
                selectedPoint = catmull.getPoint();
                isDragging = true;
                break;
            }

            catmull.setSelectedPoint(-1);
            isDragging = false;
        }
        break;

    case plugin::states::COONS:
        for (int i = 0; i < coons.getPoints().size(); ++i)
        {
            if (isInside(coons.getPoint(i)))
            {
                coons.setSelectedPoint(i);
                selectedPoint = coons.getPoint();
                isDragging = true;
                break;
            }

            coons.setSelectedPoint(-1);
            isDragging = false;
        }
        break;
    default: break;
    }
}

void plugin::states::DrawCoonsState::mouseReleased(Canvas *canvas) { isDragging = false; }

const plugin::states::curveType plugin::states::DrawCoonsState::getCurveType() const { return type; }

const ofPoint plugin::states::DrawCoonsState::getSelectedPoint() const
{
    switch (type)
    {
    case plugin::states::BEZIER: return bezier.getPoint(); break;
    case plugin::states::CATMULL_ROM: return catmull.getPoint(); break;
    case plugin::states::COONS: return coons.getPoint(); break;
    default: break;
    }
    return ofPoint();
}

const std::vector<ofPoint> plugin::states::DrawCoonsState::getPoints() const
{
    switch (type)
    {
    case plugin::states::BEZIER: {
        const auto &pointsArray = bezier.getPoints();
        return std::vector<ofPoint>(pointsArray.begin(), pointsArray.end());
        break;
    }
    case plugin::states::CATMULL_ROM: return catmull.getPoints(); break;
    case plugin::states::COONS: return coons.getPoints(); break;
    default: break;
    }

    return {};
}

void plugin::states::DrawCoonsState::setCurveType(curveType _type) { type = _type; }

void plugin::states::DrawCoonsState::setPoint(ofPoint p)
{
    switch (type)
    {
    case plugin::states::BEZIER: bezier.setPoint(p); break;
    case plugin::states::CATMULL_ROM: catmull.setPoint(p); break;
    case plugin::states::COONS: coons.setPoint(p); break;
    default: break;
    }
}

void plugin::states::DrawCoonsState::setPoints(std::vector<ofPoint> p)
{
    switch (type)
    {
    case plugin::states::BEZIER:
        if (p.size() == 3)
        {
            std::array<ofPoint, 3> pointsArray = {p[0], p[1], p[2]};
            bezier.setPoints(pointsArray);
        }
        break;
    case plugin::states::CATMULL_ROM: catmull.setPoints(p); break;
    case plugin::states::COONS: coons.setPoints(p); break;
    default: break;
    }
}

void plugin::states::DrawCoonsState::addPoint()
{
    if (type != plugin::states::CATMULL_ROM)
    {
        std::cerr << "Erreur : DrawCoonsState::addPoint() -> cette fonction ne peut etre appelee que si la courbe "
                     "active est Catmull-Rom."
                  << std::endl;
        return;
    }
    else
    {
        catmull.addPoint();
    }
}

void plugin::states::DrawCoonsState::convertCurve()
{
    if (bezier.isQuad)
    {
        bezier.toCubic();
    }
    else
    {
        bezier.toQuadratic();
    }
}

void plugin::states::DrawCoonsState::windowResized(int w, int h)
{
    float offsetX = w / 2 - 200;
    float offsetY = h / 2 - 200;
}

bool plugin::states::DrawCoonsState::isInside(ofPoint pointPos)
{
    float dx = mousePosition.x - pointPos.x;
    float dy = mousePosition.y - pointPos.y;
    float distanceSquared = dx * dx + dy * dy;

    float radiusSquared = 0.f;
    switch (type)
    {
    case plugin::states::BEZIER: radiusSquared = bezier.pointRadius * bezier.pointRadius; break;
    case plugin::states::CATMULL_ROM: radiusSquared = catmull.pointRadius * catmull.pointRadius; break;
    case plugin::states::COONS: radiusSquared = coons.pointRadius * coons.pointRadius; break;
    default: break;
    }

    return distanceSquared <= radiusSquared;
}
