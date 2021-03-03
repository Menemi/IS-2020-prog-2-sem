#pragma once

#include <cmath>
#include <vector>

using namespace std;
<<<<<<< HEAD

//fixed cpp
=======
//todo cpp
>>>>>>> 3281bdf87005ef95f014d009508c1e67e738f621
class Point {
private:
    double m_x;
    double m_y;
public:
    Point();

    Point(double x, double y);

    Point(const Point& other);

    virtual ~Point();

    double getX() const;

    double getY() const;

    Point& operator=(const Point& other);
};

class PolygonalChain : public Point {
private:
    vector<Point> m_point;
    int m_n;
public:
<<<<<<< HEAD
    PolygonalChain();
=======
    PolygonalChain() {
        //todo clear is weird here
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
>>>>>>> 3281bdf87005ef95f014d009508c1e67e738f621

    PolygonalChain(int n, Point point[]);

    PolygonalChain(const PolygonalChain& other);

    int getN() const;

<<<<<<< HEAD
    static double distance(const Point& point1, const Point& point2);
=======
    double perimeter() const override {
        //copy-paste with PolygonalChain perimeter
        double result = 0;
>>>>>>> 3281bdf87005ef95f014d009508c1e67e738f621

    PolygonalChain& operator=(const PolygonalChain& other);

    virtual double perimeter() const;

    Point getPoint(int number) const;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain();

    ClosedPolygonalChain(int n, Point* point);

    ClosedPolygonalChain(const ClosedPolygonalChain& other);

    ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other);

    double perimeter() const override;
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon();

    Polygon(int n, Point* point);

    Polygon(const Polygon& other);

    Polygon& operator=(const Polygon& other);

    virtual double area() const;
};

class Triangle : public Polygon {
public:
    Triangle();

    Triangle(int n, Point* point);

    Triangle(const Triangle& other);

    Triangle& operator=(const Triangle& other);

<<<<<<< HEAD
    bool hasRightAngle() const;
=======
        //todo sqrt then pow 2
        if (pow(a, 2) + pow(b, 2) == pow(c, 2))
            return true;
        else
            return false;
    };

    Triangle &operator=(const Triangle &other) = default;
>>>>>>> 3281bdf87005ef95f014d009508c1e67e738f621
};

class Trapezoid : public Polygon {
public:
    Trapezoid();

    Trapezoid(int n, Point* point);

    Trapezoid(const Trapezoid& other);

    Trapezoid& operator=(const Trapezoid& other);

    double height() const;
};

//todo area and perimeter for RegularPolygon
class RegularPolygon : public Polygon {
public:
    RegularPolygon();

    RegularPolygon(int n, Point* point);

    RegularPolygon(const RegularPolygon& other);

    RegularPolygon& operator=(const RegularPolygon& other);

    double area() const override;

    double perimeter() const override;
};