#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Polynomial {
private:
    int *m_coefficient;
    int *m_degree;
    int m_size;
public:
    Polynomial();

    Polynomial(int min, int max, int *coefficient);

    Polynomial(const Polynomial &other);

    ~Polynomial();

//    int getCoefficient(int number);
//
//    int getDegree(int number);
//
//    int getSize();

    Polynomial &operator=(const Polynomial &other);

    bool operator==(const Polynomial &other);

    bool operator!=(const Polynomial &other);

    Polynomial &operator+=(const Polynomial &other);

    Polynomial &operator-=(const Polynomial &other);

    Polynomial &operator+(const Polynomial &other);

    Polynomial &operator-(const Polynomial &other);

    //Polynomial &operator-(const Polynomial &other);

    Polynomial &operator*=(const Polynomial &other);

    Polynomial &operator/=(const Polynomial &other);

    Polynomial &operator*(const Polynomial &other);

    Polynomial &operator/(const Polynomial &other);

    ostream &operator<<(ostream& out, const Polynomial &other);

    ostream &operator>>(const Polynomial &other);

    Polynomial &operator[](const Polynomial &other);
};