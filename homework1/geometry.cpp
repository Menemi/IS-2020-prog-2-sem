#define _USE_MATH_DEFINES

#include "geometry.h"
#include <cmath>
#include <vector>

using namespace std;

Point::Point() {
    m_x = 0;
    m_y = 0;
}

Point::Point(double x, double y) {
    m_x = x;
    m_y = y;
}

Point::Point(const Point &other) {
    m_x = other.m_x;
    m_y = other.m_y;
}

Point::~Point() = default;

double Point::getX() const { return m_x; }

double Point::getY() const { return m_y; }

Point &Point::operator=(const Point &other) = default;

PolygonalChain::PolygonalChain() {
    //fixed clear is weird here
    m_n = 0;
}

PolygonalChain::PolygonalChain(int n, Point point[]) {
    m_n = n;
    for (int i = 0; i < n; i++) {
        m_point.push_back(point[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain &other) : Point(other) {
    m_n = other.m_n;
    m_point = other.m_point;
}

Point PolygonalChain::getPoint(int number) const {
    return m_point[number];
}

int PolygonalChain::getN() const { return m_n; }

double PolygonalChain::distance(const Point &point1, const Point &point2) {
    return sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
}

double PolygonalChain::perimeter() const {
    double result = 0;

    for (int i = 0; i < getN() - 1; i++) {
        result += distance(getPoint(i), getPoint(i + 1));
    }
    return result;
}

PolygonalChain &PolygonalChain::operator=(const PolygonalChain &other) = default;

ClosedPolygonalChain::ClosedPolygonalChain() : PolygonalChain() {}

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point *point) : PolygonalChain(n, point) {}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &other) = default;

double ClosedPolygonalChain::perimeter() const {
    //todo copy-paste with PolygonalChain perimeter
    double result = 0;
    result = PolygonalChain::perimeter();
    result += distance(getPoint(getN() - 1), getPoint(0));

    return result;
}

ClosedPolygonalChain &ClosedPolygonalChain::operator=(const ClosedPolygonalChain &other) = default;

Polygon::Polygon() : ClosedPolygonalChain() {}

Polygon::Polygon(int n, Point *point) : ClosedPolygonalChain(n, point) {}

Polygon::Polygon(const Polygon &other) = default;

double Polygon::area() const {
    double result1 = 0, result2 = 0, result;
    for (int i = 0; i < getN() - 1; i++) {
        result1 += getPoint(i).getX() * getPoint(i + 1).getY();
    }
    result1 += getPoint(getN() - 1).getX() * getPoint(0).getY();

    for (int i = 0; i < getN() - 1; i++) {
        result2 += getPoint(i).getY() * getPoint(i + 1).getX();
    }
    result2 += getPoint(getN() - 1).getY() * getPoint(0).getX();

    result = abs(result1 - result2);
    return result / 2;
}

Polygon &Polygon::operator=(const Polygon &other) = default;

Triangle::Triangle() : Polygon() {}

Triangle::Triangle(int n, Point *point) : Polygon(n, point) {}

Triangle::Triangle(const Triangle &other) = default;

bool Triangle::hasRightAngle() const {
    double a, b, c;
    a = pow(getPoint(0).getX() - getPoint(1).getX(), 2) +
        pow(getPoint(0).getY() - getPoint(1).getY(), 2);
    b = pow(getPoint(1).getX() - getPoint(2).getX(), 2) +
        pow(getPoint(1).getY() - getPoint(2).getY(), 2);
    c = pow(getPoint(2).getX() - getPoint(0).getX(), 2) +
        pow(getPoint(2).getY() - getPoint(0).getY(), 2);

    if (a > b)
        swap(a, b);
    if (b > c) {
        swap(b, c);
    }

    //fixed sqrt then pow 2
    if (a + b == c)
        return true;
    else
        return false;
}

Triangle &Triangle::operator=(const Triangle &other) = default;

Trapezoid::Trapezoid() : Polygon() {}

Trapezoid::Trapezoid(int n, Point *point) : Polygon(n, point) {}

Trapezoid::Trapezoid(const Trapezoid &other) = default;

double Trapezoid::height() const {
    double tempSide1, timeSide2;
    tempSide1 = distance(getPoint(1), getPoint(2));
    timeSide2 = distance(getPoint(3), getPoint(0));
    double result = area() * 2 / (tempSide1 + timeSide2);

    return result;
}

Trapezoid &Trapezoid::operator=(const Trapezoid &other) = default;

//fixed area and perimeter for RegularPolygon
RegularPolygon::RegularPolygon() : Polygon() {}

RegularPolygon::RegularPolygon(int n, Point *point) : Polygon(n, point) {}

RegularPolygon::RegularPolygon(const RegularPolygon &other) = default;

RegularPolygon &RegularPolygon::operator=(const RegularPolygon &other) = default;

double RegularPolygon::area() const {
    double side = distance(getPoint(0), getPoint(1));
    int n = getN();
    return ((n * pow(side, 2)) / (4 * tan(M_PI / n)));
}

double RegularPolygon::perimeter() const {
    double side = distance(getPoint(0), getPoint(1));
    return side * getN();
}

