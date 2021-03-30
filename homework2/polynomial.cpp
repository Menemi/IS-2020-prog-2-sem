#include "polynomial.h"

Polynomial::Polynomial() {
    m_coefficient = new int[1]{0};
    m_degree = new int[1]{0};
    m_size = 1;
}

Polynomial::Polynomial(int min, int max, int *coefficient) {
    int size = max - min + 1;
    int tempDegree = min;

    m_degree = new int[size];
    m_coefficient = new int[size];
    m_size = size;

    for (int i = 0; i < size; i++) {
        m_degree[i] = tempDegree;
        m_coefficient[i] = *coefficient;
        tempDegree++;
        coefficient++;
    }
}

Polynomial::Polynomial(const Polynomial &other) {
    m_size = other.m_size;

    m_coefficient = new int[m_size];
    m_degree = new int[m_size];

    for (int i = 0; i < m_size; i++) {
        m_degree[i] = other.m_degree[i];
        m_coefficient[i] = other.m_coefficient[i];
    }
}

Polynomial::~Polynomial() {
    delete[] m_coefficient;
    delete[] m_degree;
}

stringstream &operator<<(stringstream &out, const Polynomial &other) {
    int tempSize = other.m_size;

    if (tempSize == 1 && other.m_coefficient[0] == 0) {
        out << "0";
    } else {
        for (int i = tempSize - 1; i >= 0; i--) {
            if (other.m_coefficient[i] != 0) {

                if (i < tempSize - 1 && other.m_coefficient[i] > 0 && !out.str().empty() && out.str().back() != '\n')
                    out << "+";
                if (other.m_coefficient[i] == -1 && other.m_degree[i] != 0)
                    out << "-";
                else if (other.m_coefficient[i] == 1 && other.m_degree[i] != 0) {}
                else
                    out << other.m_coefficient[i];

                if (other.m_degree[i] != 0) {
                    out << "x";
                    if (other.m_degree[i] != 1)
                        out << "^" << other.m_degree[i];
                }
            }
        }
    }

    int temp = 0;

    for (int i = 0; i < other.m_size; i++) {
        if (other.m_coefficient[i] == 0)
            temp++;
    }

    if (temp == other.m_size && out.str().empty())
        out << "0";
    return out;
}

Polynomial &Polynomial::operator=(const Polynomial &other) {
    if (&other == this)
        return *this;

    delete[] m_coefficient;
    delete[] m_degree;
    m_size = other.m_size;
    m_coefficient = new int[m_size];
    m_degree = new int[m_size];

    for (int i = 0; i < m_size; i++) {
        m_coefficient[i] = other.m_coefficient[i];
        m_degree[i] = other.m_degree[i];
    }
    return *this;
}

bool operator==(const Polynomial &other1, const Polynomial &other2) {
    stringstream ss1, ss2;
    ss1 << other1;
    ss2 << other2;
    auto temp1 = ss1.str();
    auto temp2 = ss2.str();
    return ss1.str() == ss2.str();
}

bool operator!=(const Polynomial &other1, const Polynomial &other2) {
    return !(other1 == other2);
}

Polynomial operator+(const Polynomial &other1, const Polynomial &other2) {
    Polynomial temp = Polynomial(other1);
    temp += other2;
    return temp;
}

Polynomial Polynomial::operator-() const {
    Polynomial temp = *this;
    for (int i = 0; i < m_size; i++) {
        temp.m_coefficient[i] = -m_coefficient[i];
    }
    return temp;
}

//todo without creating new object
Polynomial operator-(const Polynomial &other1, const Polynomial &other2) {
    return other1 + (-other2);
}

Polynomial Polynomial::operator+=(const Polynomial &other) {
    int tempMin = min(m_degree[0], other.m_degree[0]);
    int tempMax = max(m_degree[m_size - 1], other.m_degree[other.m_size - 1]);
    int tempSize = tempMax - tempMin + 1;
    int tempCoefficient[tempSize];
    int counter = tempMin;

    for (int i = 0; i < tempSize; i++) {
        tempCoefficient[i] = 0;

        for (int j = 0; j < m_size; j++) {
            if (m_degree[j] == counter) {
                tempCoefficient[i] += m_coefficient[j];
            }
        }

        for (int j = 0; j < other.m_size; j++) {
            if (other.m_degree[j] == counter) {
                tempCoefficient[i] += other.m_coefficient[j];
            }
        }
        counter++;
    }

    *this = Polynomial(tempMin, tempMax, tempCoefficient);

    return *this;
}

Polynomial Polynomial::operator-=(const Polynomial &other) {
    *this = *this - other;
    return *this;
}

Polynomial operator*(const Polynomial &other, int number) {
    int *tempCoefficient = new int[other.m_size];

    for (int i = 0; i < other.m_size; i++) {
        tempCoefficient[i] = other.m_coefficient[i] * number;
    }

    return Polynomial(other.m_degree[0], other.m_degree[other.m_size - 1], tempCoefficient);
}

Polynomial operator*(int number, const Polynomial &other) {
    return other * number;
}

Polynomial operator*(const Polynomial &other1, const Polynomial &other2) {
    int tempSize = other1.m_size * other2.m_size;
    int tempCoefficient[tempSize], tempDegree[tempSize];
    int index = 0;

    for (int i = 0; i < other1.m_size; i++) {
        for (int j = 0; j < other2.m_size; j++) {
            tempCoefficient[index] = other1.m_coefficient[i] * other2.m_coefficient[j];
            tempDegree[index] = other1.m_degree[i] + other2.m_degree[j];
            index++;
        }
    }

    int size = tempDegree[tempSize - 1] - tempDegree[0] + 1;
    int resultDegree[size], resultCoefficient[size];
    index = tempDegree[0];

    for (int i = 0; i < size; i++) {
        resultDegree[i] = index;
        resultCoefficient[i] = 0;
        index++;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < tempSize; j++) {
            if (tempDegree[j] == resultDegree[i])
                resultCoefficient[i] += tempCoefficient[j];
        }
    }

    return Polynomial(tempDegree[0], tempDegree[tempSize - 1], resultCoefficient);
}

Polynomial Polynomial::operator/(int number) {
    auto temp = *this;
    for_each(temp.m_coefficient, temp.m_coefficient + temp.m_size, [&](int &n) { n /= number; });
    return temp;
}

Polynomial Polynomial::operator*=(const Polynomial &other) {
    *this = *this * other;
    return *this;
}

Polynomial Polynomial::operator/=(int number) {
    *this = *this / number;
    return *this;
}

int Polynomial::operator[](int number) const {
    if (number >= m_degree[0] && number <= m_degree[m_size - 1]) {
        int index = 0;
        for (int i = 0; i < m_size; i++) {
            if (number == m_degree[i]) {
                index = i;
                break;
            }
        }
        return m_coefficient[index];
    } else
        return 0;
}

int &Polynomial::operator[](int number) {
    if (number >= m_degree[0] && number <= m_degree[m_size - 1]) {
        int index = 0;
        for (int i = 0; i < m_size; i++) {
            if (number == m_degree[i]) {
                index = i;
                break;
            }
        }
        return m_coefficient[index];
    } else if (number < m_degree[0]) {
        int max = m_degree[m_size - 1];
        int min = number;
        int tempSize = max - min + 1;
        int tempCoefficient[tempSize];

        for (int i = 0; i < tempSize; i++)
            tempCoefficient[i] = 0;

        for (int i = 1; i < m_size; i++)
            tempCoefficient[tempSize - i] = m_coefficient[m_size - i];

        *this = Polynomial(min, max, tempCoefficient);
        return m_coefficient[0];
    } else {
        int max = number;
        int min = m_degree[0];
        int tempSize = max - min + 1;
        int tempCoefficient[tempSize];

        for (int i = 0; i < tempSize; i++)
            tempCoefficient[i] = 0;

        for (int i = 0; i < m_size; i++)
            tempCoefficient[i] = m_coefficient[i];

        *this = Polynomial(min, max, tempCoefficient);
        return m_coefficient[m_size - 1];
    }
}

double Polynomial::get(int number) {
    double temp = m_coefficient[0] * pow(number, m_degree[0]);
    double result = temp;

    for (int i = 1; i < m_size; i++) {
        temp *= number;
        result += m_coefficient[i] * temp;
    }

    return result;
}