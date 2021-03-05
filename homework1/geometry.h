#pragma once

#include <cmath>
#include <vector>

using namespace std;

//fixed cpp
class Point {
private:
    double m_x;
    double m_y;
public:
    Point();

    Point(double x, double y);

    Point(const Point &other);

    virtual ~Point();

    double getX() const;

    double getY() const;

    Point &operator=(const Point &other);
};

class PolygonalChain : public Point {
private:
    vector<Point> m_point;
    int m_n;
public:
    PolygonalChain();

    PolygonalChain(int n, Point point[]);

    PolygonalChain(const PolygonalChain &other);

    int getN() const;

    static double distance(const Point &point1, const Point &point2);

    PolygonalChain &operator=(const PolygonalChain &other);

    virtual double perimeter() const;

    Point getPoint(int number) const;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain();

    ClosedPolygonalChain(int n, Point *point);

    ClosedPolygonalChain(const ClosedPolygonalChain &other);

    ClosedPolygonalChain &operator=(const ClosedPolygonalChain &other);

    double perimeter() const override;
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon();

    Polygon(int n, Point *point);

    Polygon(const Polygon &other);

    Polygon &operator=(const Polygon &other);

    virtual double area() const;
};

class Triangle : public Polygon {
public:
    Triangle();

    Triangle(int n, Point *point);

    Triangle(const Triangle &other);

    Triangle &operator=(const Triangle &other);

    bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
    Trapezoid();

    Trapezoid(int n, Point *point);

    Trapezoid(const Trapezoid &other);

    Trapezoid &operator=(const Trapezoid &other);

    double height() const;
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon();

    RegularPolygon(int n, Point *point);

    RegularPolygon(const RegularPolygon &other);

    RegularPolygon &operator=(const RegularPolygon &other);

    double area() const override;

    double perimeter() const override;
};