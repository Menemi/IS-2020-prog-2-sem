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

    friend bool operator==(const Polynomial &other1, const Polynomial &other2);

    friend bool operator!=(const Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator+(const Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator-(const Polynomial &other);

    friend Polynomial operator-(const Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator+=(Polynomial &other1, const Polynomial &other2);

    friend Polynomial operator-=(Polynomial &other1, const Polynomial &other2);
};