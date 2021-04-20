#pragma once

#include <string>
#include <vector>

using namespace std;

class Analysis {
public:
    Analysis() {}

    void setID(int);

    void setType(const string &);

    void setStreets(const string &);

    void setRoutes(const string &);

    void setCoords(const string &);

    string getType() const;

    const vector<string> &getStreets() const;

    const vector<string> &getRoutes() const;

    pair<double, double> getCoords() const;

    static double length(const vector<pair<double, double>> &);


private:
    int id;
    string type;
    vector<string> streets;
    vector<string> routes;
    pair<double, double> coords;

    static vector<string> split(const string &, char) ;

    static string replace(const string &, const string &, const string &) ;
};