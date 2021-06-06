#pragma once

#include <string>
#include <vector>

using namespace std;

class Analysis {
private:
    string type;
    vector<string> streets;
    vector<string> routes;
    pair<double, double> coord;

    static string replace(const string &, const string &, const string &);

public:
    Analysis() {};

    void setType(const string &type);

    void setStreets(const string &str);

    void setRoutes(const string &str);

    void setCoords(const string &str);

    string getType() const;

    const vector<string> &getStreets() const;

    const vector<string> &getRoutes() const;

    pair<double, double> getCoords() const;

    static double length(const vector<pair<double, double>> &stops);
};