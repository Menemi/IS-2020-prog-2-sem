#pragma once

#include <cmath>
#include <vector>

using namespace std;

class Point {
private:
    double m_x;
    double m_y;
public:
    Point() {
        m_x = 0;
        m_y = 0;
    };

    Point(double x, double y) {
        m_x = x;
        m_y = y;
    };

    Point(const Point &other) {
        m_x = other.m_x;
        m_y = other.m_y;
    };

    virtual ~Point() = default;

    double getX() const { return m_x; };

    double getY() const { return m_y; };

    Point &operator=(const Point &other) = default;
};

class PolygonalChain : public Point {
private:
    vector<Point> m_point;
    int m_n;
public:
    PolygonalChain() {
        m_n = 0;
        m_point.clear();
    };

    PolygonalChain(int n, Point point[]) {
        m_n = n;
        for (int i = 0; i < n; i++) {
            m_point.push_back(point[i]);
        }
    };

    PolygonalChain(const PolygonalChain &other) : Point(other) {
        m_n = other.m_n;
        m_point = other.m_point;
    };

    Point getPoint(int number) const {
        return m_point[number];
    };

    int getN() const { return m_n; };

    static double distance(const Point &point1, const Point &point2) {
        return sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
    };

    virtual double perimeter() const {
        double result = 0;

        for (int i = 0; i < getN() - 1; i++) {
            result += distance(getPoint(i), getPoint(i + 1));
        }
        return result;
    };

    PolygonalChain &operator=(const PolygonalChain &other) = default;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() : PolygonalChain() {};

    ClosedPolygonalChain(int n, Point *point) : PolygonalChain(n, point) {};

    ClosedPolygonalChain(const ClosedPolygonalChain &other) = default;

    double perimeter() const override {
        double result = 0;

        for (int i = 0; i < getN() - 1; i++)
            result += distance(getPoint(i), getPoint(i + 1));
        result += distance(getPoint(getN() - 1), getPoint(0));

        return result;
    };

    ClosedPolygonalChain &operator=(const ClosedPolygonalChain &other) = default;
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon() : ClosedPolygonalChain() {};

    Polygon(int n, Point *point) : ClosedPolygonalChain(n, point) {};

    Polygon(const Polygon &other) = default;

    virtual double area() const {
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
    };

    Polygon &operator=(const Polygon &other) = default;
};

class Triangle : public Polygon {
public:
    Triangle() : Polygon() {};

    Triangle(int n, Point *point) : Polygon(n, point) {};

    Triangle(const Triangle &other) = default;

    bool hasRightAngle() const {
        double a, b, c;
        a = distance(getPoint(0), getPoint(1));
        b = distance(getPoint(1), getPoint(2));
        c = distance(getPoint(2), getPoint(0));

        if (a > b)
            swap(a, b);
        if (b > c) {
            swap(b, c);
        }

        if (pow(a, 2) + pow(b, 2) == pow(c, 2))
            return true;
        else
            return false;
    };

    Triangle &operator=(const Triangle &other) = default;
};

class Trapezoid : public Polygon {
public:
    Trapezoid() : Polygon() {};

    Trapezoid(int n, Point *point) : Polygon(n, point) {};

    Trapezoid(const Trapezoid &other) = default;

    double height() const {
        double tempSide1, timeSide2;
        tempSide1 = distance(getPoint(1), getPoint(2));
        timeSide2 = distance(getPoint(3), getPoint(0));
        double result = area() * 2 / (tempSide1 + timeSide2);

        return result;
    };

    Trapezoid &operator=(const Trapezoid &other) = default;
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon() : Polygon() {};

    RegularPolygon(int n, Point *point) : Polygon(n, point) {};

    RegularPolygon(const RegularPolygon &other) = default;

    RegularPolygon &operator=(const RegularPolygon &other) = default;
};