#include <cmath>
#include "analysis.h"

using namespace std;

const int MERIDIAN_DEGREE = 110;
const int LATITUDE = 58;

string Analysis::replace(const string &String, const string &string1, const string &string2) {
    string tempString = String;

    int i;
    while ((i = tempString.find(string1)) != string::npos)
        tempString.replace(i, string1.length(), string2);

    return tempString;
}

void Analysis::setType(const string &otherType) {
    type = otherType;
}

void Analysis::setStreets(const string &otherStreets) {
    if (otherStreets.length() > 0) {
        int prev = 0;

        for (int i = 0; i < otherStreets.length() - 1; i++)
            if (otherStreets[i] == ',') {
                streets.push_back(otherStreets.substr(prev, i - prev));
                prev = i + 1;
            }

        streets.push_back(otherStreets.substr(prev));
    }
}

void Analysis::setRoutes(const string &otherRoutes) {
    if (otherRoutes.length() > 0) {
        string tempString = replace(otherRoutes, ".", ",");
        int prev = 0;

        for (int i = 0; i < otherRoutes.length() - 1; i++)
            if (otherRoutes[i] == ',') {
                routes.push_back(otherRoutes.substr(prev, i - prev));
                prev = i + 1;
            }

        routes.push_back(otherRoutes.substr(prev));
    }
}

void Analysis::setCoords(const string &otherCoords) {
    vector<string> tokens;
    int prev = 0;

    for (int i = 0; i < otherCoords.length() - 1; i++)
        if (otherCoords[i] == ',') {
            tokens.push_back(otherCoords.substr(prev, i - prev));
            prev = i + 1;
        }

    tokens.push_back(otherCoords.substr(prev));
    coord = {atof(tokens[0].c_str()), atof(tokens[1].c_str())};
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
    return coord;
}

double distance(pair<double, double> coord1, pair<double, double> coord2) {
    return sqrt(pow((coord1.first - coord2.first) * MERIDIAN_DEGREE, 2) +
                pow((coord1.second - coord2.second) * LATITUDE, 2));
}

double Analysis::length(const vector<pair<double, double>> &stops) {
    double length = 0;
    int next = 0;
    vector<bool> visited(stops.size(), false);

    while (next != stops.size()) {
        int cur = next;
        visited[cur] = true;
        double minDist = INT64_MAX;
        next = stops.size();

        for (int i = 0; i < stops.size(); i++) {
            if (visited[i])
                continue;

            double dist;

            if ((dist = distance(stops[cur], stops[i])) < minDist) {
                minDist = dist;
                next = i;
            }
        }

        if (next < stops.size()) {
            for (int i = 0; i < stops.size(); i++) {
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