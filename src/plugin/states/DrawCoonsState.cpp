#include "DrawCoonsState.hpp"

plugin::states::DrawCoonsState::DrawCoonsState()
    : coons(ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f), ofPoint(0.0f, 0.0f, 0.0f))
{
}

void plugin::states::DrawCoonsState::enter()
{
    ofBackground(255);
    ofSetColor(0);

    float w = ofGetWidth();
    float h = ofGetHeight();

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
        coons.setPoint(newPoint);
    }
}

void plugin::states::DrawCoonsState::draw() { coons.draw(); }

void plugin::states::DrawCoonsState::exit() { coons.~Coons(); }

void plugin::states::DrawCoonsState::mouseDragged(int x, int y, int button)
{
    if (isDragging)
    {
        ofPoint newPoint(x, y, selectedPoint.z);
        coons.setPoint(newPoint);
    }
}

void plugin::states::DrawCoonsState::mousePressed(int x, int y, int button)
{
    for (int i = 0; i < coons.getPoints().size(); ++i)
    {
        if (isInside(coons.getPoint(i)))
        {
            coons.setSelectedPoint(i);
            selectedPoint = coons.getPoint();
            isDragging = true;
            break;
        }
        else
        {
            coons.setSelectedPoint(-1);
            isDragging = false;
        }
    }
}

void plugin::states::DrawCoonsState::mouseReleased(Canvas *canvas) { isDragging = false; }

const ofPoint plugin::states::DrawCoonsState::getSelectedPoint() const { return coons.getPoint(); }

const std::vector<ofPoint> plugin::states::DrawCoonsState::getPoints() const { return coons.getPoints(); }

void plugin::states::DrawCoonsState::setPoint(ofPoint p) { coons.setPoint(p); }

void plugin::states::DrawCoonsState::setPoints(std::vector<ofPoint> p) { coons.setPoints(p); }

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
    float radiusSquared = coons.pointRadius * coons.pointRadius;

    return distanceSquared <= radiusSquared;
}
