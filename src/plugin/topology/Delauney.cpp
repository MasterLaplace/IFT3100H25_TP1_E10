#include "Delauney.hpp"  
#include "ofMain.h"  

void Delauney::setup() 
{
    
    // On génère aléatoirement des triangles.
    shuffle();
}

void Delauney::triangulate(const std::vector<Point> &points)
{
    triangles.clear();

    // Triangle super géant (à ajuster selon tes données)
    float margin = 10000;
    Point p1(-margin, -margin);
    Point p2(2 * margin, -margin);
    Point p3(0, 2 * margin);

    triangles.emplace_back(p1, p2, p3);

    for (const Point &point : points)
    {
        std::vector<Triangle> badTriangles;
        std::vector<std::pair<Point, Point>> polygon;

        // Étape 1 : trouver les triangles dont le cercle contient le point
        for (const auto &tri : triangles)
        {
            if (isPointInsideCircumcircle(point, tri))
            {
                badTriangles.push_back(tri);
            }
        }

        // Étape 2 : trouver les bords du "trou" (côtés non partagés)
        for (const auto &badTri : badTriangles)
        {
            for (int i = 0; i < 3; ++i)
            {
                Point a = badTri.vertices[i];
                Point b = badTri.vertices[(i + 1) % 3];
                if (!isSharedEdge(a, b, badTriangles))
                {
                    polygon.emplace_back(a, b);
                }
            }
        }

        // Étape 3 : supprimer les mauvais triangles
        for (const auto &tri : badTriangles)
        {
            removeTriangle(tri);
        }

        // Étape 4 : ajouter les nouveaux triangles
        for (const auto &edge : polygon)
        {
            triangles.emplace_back(edge.first, edge.second, point);
        }
    }

    // Étape 5 : supprimer les triangles connectés au triangle super géant
    triangles.erase(std::remove_if(triangles.begin(), triangles.end(),[&](const Triangle &t) 
        {
            return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
        }),
      triangles.end());
}

void Delauney::draw() 
{
    ofBackground(255); // Fond blanc

    // Dessiner tous les points
    for (const auto &point : points)
    {
        ofSetColor(ofColor::black);
        ofDrawCircle(point.x, point.y, 3.0f);
    }

    // Dessiner le point sélectionné
    if (selectedPoint.x != -1.0f && selectedPoint.y != -1.0f)
    {
        ofSetColor(ofColor::red); // Couleur rouge pour le point sélectionné
        ofDrawCircle(selectedPoint.x, selectedPoint.y, 5.0f);
    }

    // On dessine les triangles
    ofSetColor(0);
    for (const auto &tri : triangles)
    {
        ofDrawLine(tri.vertices[0].x, tri.vertices[0].y, tri.vertices[1].x, tri.vertices[1].y);
        ofDrawLine(tri.vertices[1].x, tri.vertices[1].y, tri.vertices[2].x, tri.vertices[2].y);
        ofDrawLine(tri.vertices[2].x, tri.vertices[2].y, tri.vertices[0].x, tri.vertices[0].y);
    }
}

void Delauney::shuffle() 
{
    generateRandomPoints(10, ofGetWidth(), ofGetHeight(), points);
    triangulate(points);
}

void Delauney::onMousePressed(int x, int y) 
{
    const float tolerance = 5.0f; // Tolérance pour détecter un clic proche d'un point
    for (const auto &point : points)
    {
        float dx = x - point.x;
        float dy = y - point.y;
        if (dx * dx + dy * dy <= tolerance * tolerance)
        {
            selectedPoint = point; // Met à jour le point sélectionné
            isDragging = true;
            return;
        }
    }
    selectedPoint = Point(-1.0f, -1.0f); // Aucun point sélectionné
    isDragging = false;
}

void Delauney::onMouseDragged(int x, int y) 
{
    if (isDragging && selectedPoint.x != -1.0f && selectedPoint.y != -1.0f)
    {
        // Met à jour la position du point sélectionné
        for (auto &point : points)
        {
            if (point == selectedPoint)
            {
                point.x = x;
                point.y = y;
                selectedPoint = point; // Met à jour la position du point sélectionné
                break;
            }
        }

        // Recalculer la triangulation en temps réel
        triangulate(points);
    }
}

void Delauney::onMouseReleased() 
{ 
    isDragging = false; 
}

void Delauney::setPoint(Point newPoint) 
{
    for (auto &point : points)
    {
        if (point.x == selectedPoint.x && point.y == selectedPoint.y)
        {
            point = newPoint;
            triangulate(points);
            return;
        }
    }
    std::cout << "Aucun point trouvé pour mettre à jour." << std::endl;
}

void Delauney::addPoint() 
{ 
    float x = ofGetWidth() / 2;
    float y = ofGetHeight() / 2;
    points.emplace_back(x, y);
    selectedPoint = Point(x, y);
    triangulate(points);
}

void Delauney::removeSelectedPoint()
{
    if (selectedPoint.x != -1.0f && selectedPoint.y != -1.0f)
    {
        points.erase(std::remove_if(points.begin(), points.end(),
                                    [&](const Point &p) { return p.x == selectedPoint.x && p.y == selectedPoint.y; }),
                     points.end());
        selectedPoint = Point(-1.0f, -1.0f);
        triangulate(points);
    }
}


void Delauney::generateRandomPoints(int count, float width, float height, std::vector<Point> &points) 
{
    points.clear();
    for (int i = 0; i < count; ++i)
    {
        float x = ofRandom(50, width - 50);
        float y = ofRandom(50, height - 50);
        points.emplace_back(x, y);
    }
}

void Delauney::removeTriangle(const Triangle &tri)
{
    triangles.erase(std::remove(triangles.begin(), triangles.end(), tri), triangles.end());
}

bool Delauney::isPointInsideCircumcircle(const Point &p, const Triangle &t) 
{ 
    const auto &a = t.vertices[0];
    const auto &b = t.vertices[1];
    const auto &c = t.vertices[2];

    float ax = a.x - p.x;
    float ay = a.y - p.y;
    float bx = b.x - p.x;
    float by = b.y - p.y;
    float cx = c.x - p.x;
    float cy = c.y - p.y;

    float det =
        (ax * (by * (cx * cx + cy * cy) - cy * (bx * bx + by * by)) -
         ay * (bx * (cx * cx + cy * cy) - cx * (bx * bx + by * by)) + (ax * ax + ay * ay) * (bx * cy - by * cx));

    return det > 0;
}

bool Delauney::isSharedEdge(const Point &a, const Point &b, const std::vector<Triangle> &tris) 
{ 
    int count = 0;
    for (const auto &t : tris)
    {
        for (int i = 0; i < 3; ++i)
        {
            Point tA = t.vertices[i];
            Point tB = t.vertices[(i + 1) % 3];
            if ((tA.x == a.x && tA.y == a.y && tB.x == b.x && tB.y == b.y) ||
                (tA.x == b.x && tA.y == b.y && tB.x == a.x && tB.y == a.y))
            {
                count++;
            }
        }
    }
    return count > 1;
}
