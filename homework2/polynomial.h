#pragma once

#include "cmath"
#include "sstream"

using namespace std;

class Polynomial {
private:
    int *m_degree;
    int *m_coefficient;
    int m_size;
public:
    Polynomial();

    Polynomial(int min, int max, int *coefficient);

    Polynomial(const Polynomial &other);

    ~Polynomial();

    friend stringstream &operator<<(stringstream &out, const Polynomial &other);

    Polynomial &operator=(const Polynomial &other);

    //todo $= is inside class, $ friend function
    friend bool operator==(const Polynomial &other1, const Polynomial &other2);

    friend bool operator!=(const Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator+(const Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator-(const Polynomial &other);

    friend Polynomial operator-(const Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator+=(Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator-=(Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator*(const Polynomial &other, int number);

    friend Polynomial operator*(int number, const Polynomial &other);

    friend Polynomial operator*(const Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator/(const Polynomial &other, int number);

    friend Polynomial operator*=(Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator/=(Polynomial &other, int number);

    int &operator[](int i);

    int &operator[](int number) const;

    double get(int number);
};