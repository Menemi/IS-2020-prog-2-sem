#include <cmath>
#include "analysis.h"

using namespace std;

const int MERIDIAN_DEGREE = 110;
const int LATITUDE = 58;

void Analysis::setID(unsigned id) {
    this->id = id;
}

void Analysis::setType(const string &type) {
    this->type = type;
}

void Analysis::setStreets(const string &String) {
    if (String.length() > 0)
        streets = split(String, ',');
}

void Analysis::setRoutes(const string &String) {
    if (String.length() > 0)
        routes = split(replace(String, ".", ","), ',');
}

void Analysis::setCoords(const string &String) {
    vector<string> tokens = split(String, ',');
    cord = {atof(tokens[0].c_str()), atof(tokens[1].c_str())};
}

string Analysis::getType() const {
    return type;
}

const vector<string> &Analysis::getStreets() const {
    return streets;
}

const vector<string> &Analysis::getRoutes() const {
    return routes;
}

pair<double, double> Analysis::getCoords() const {
    return cord;
}

vector<string> Analysis::split(const string &String, char ch1) {
    vector<string> result;
    size_t prev = 0;

    for (size_t i = 0; i < String.length() - 1; i++)
        if (String[i] == ch1) {
            result.push_back(String.substr(prev, i - prev));
            prev = i + 1;
        }

    result.push_back(String.substr(prev));
    return result;
}

string Analysis::replace(const string &String, const string &s1, const string &s2) {
    string temp = String;
    size_t i;

    while ((i = temp.find(s1)) != string::npos)
        temp.replace(i, s1.length(), s2);

    return temp;
}

double distance(pair<double, double> other1, pair<double, double> other2) {
    return sqrt(pow((other1.first - other2.first) * MERIDIAN_DEGREE, 2) +
                pow((other1.second - other2.second) * LATITUDE, 2));
}

double Analysis::length(const vector<pair<double, double>> &stops) {
    double length = 0;
    size_t next = 0;
    vector<bool> visited(stops.size(), false);

    while (next != stops.size()) {
        size_t cur = next;
        visited[cur] = true;
        double minDist = INT64_MAX;
        next = stops.size();

        for (size_t i = 0; i < stops.size(); i++) {
            if (visited[i])
                continue;

            double dist;

            if ((dist = distance(stops[cur], stops[i])) < minDist) {
                minDist = dist;
                next = i;
            }
        }

        if (next < stops.size()) {
            for (size_t i = 0; i < stops.size(); i++) {
                if (!visited[i])
                    continue;

                double dist = distance(stops[next], stops[i]);
                if (dist < minDist)
                    minDist = dist;
            }

            length += minDist;
        }
    }
    return length;
}