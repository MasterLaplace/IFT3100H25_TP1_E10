#pragma once

#include <vector>
#include <array>
#include <glm/vec2.hpp>
#include <ofPoint.h>

//------------------------------------------------------------------------
// Structure maison pour representer un point 2D.
struct Point {
    float x, y;

    Point(float _x = 0, float _y = 0) : x(_x), y(_y) {}
    bool operator==(const Point &other) const { return x == other.x && y == other.y; }
};
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Structure maison pour representer un triangle.
struct Triangle {
    std::array<Point, 3> vertices;

    Triangle(Point a, Point b, Point c) { vertices = {a, b, c}; }

    bool containsVertex(const Point &p) const
    {
        for (const auto &v : vertices)
            if (v.x == p.x && v.y == p.y)
                return true;
        return false;
    }

    bool operator==(const Triangle &other) const
    {
        // Check if all vertices match (order does not matter)
        for (const auto &v : vertices)
        {
            bool found = false;
            for (const auto &ov : other.vertices)
            {
                if (v.x == ov.x && v.y == ov.y)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
        }
        return true;
    }
};
//------------------------------------------------------------------------


//------------------------------------------------------------------------
class Delauney {
public: 
    void setup();
    void draw();
    void shuffle();

    void onMousePressed(int x, int y);
    void onMouseDragged(int x, int y);
    void onMouseReleased();

    Point getSelectedPoint() { return selectedPoint; }

    void setPoint(Point newPoint);

    void addPoint();
    void removeSelectedPoint();
	
private:
    std::vector<Point> points;
    std::vector<Triangle> triangles;
    Point selectedPoint = Point(-1.0f, -1.0f);
    bool isDragging = false;

    void triangulate(const std::vector<Point> &points);
    void generateRandomPoints(int count, float width, float height, std::vector<Point> &points);
    void removeTriangle(const Triangle &tri);
    bool isPointInsideCircumcircle(const Point &p, const Triangle &t);
    bool isSharedEdge(const Point &a, const Point &b, const std::vector<Triangle> &tris);
};
