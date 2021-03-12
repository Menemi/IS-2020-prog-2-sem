#include "polynomial.h"

Polynomial::Polynomial() {
    m_coefficient = new int[1]{0};
    m_degree = new int[1]{0};
    m_size = 1;
}

Polynomial::Polynomial(int min, int max, int *coefficient) {
    int size = max - min + 1;
    int tempDegree = min;

    m_coefficient = coefficient;
    m_size = size;
    m_degree = new int[size];

    for (int i = 0; i < size; i++) {
        m_degree[i] = tempDegree;
        tempDegree++;
    }
}

Polynomial::Polynomial(const Polynomial &other) {
    m_coefficient = other.m_coefficient;
    m_degree = other.m_degree;
    m_size = other.m_size;
}

Polynomial::~Polynomial() = default;

//int Polynomial::getSize() {
//    return m_size;
//}
//
//int Polynomial::getDegree(int number) {
//    return m_degree[number];
//}
//
//int Polynomial::getCoefficient(int number) {
//    return m_coefficient[number];
//}

Polynomial &Polynomial::operator=(const Polynomial &other) = default;

ostream & Polynomial::operator<<(ostream &out, const Polynomial &other) {
    if (m_coefficient[0] != 0) {
        out << m_coefficient[0] << "x^" <<  m_degree[0];
    }

    for (int i = 0; i < m_size; i++){
        if (m_coefficient[i] != 0) {

        }
    }

    return out;
}



















