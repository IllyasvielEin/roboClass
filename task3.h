//
// Created by Illyasviel on 2021/9/30.
//

#ifndef ROBOCLASS_TASK3_H
#define ROBOCLASS_TASK3_H
#include "vecposition.h"
#include <stack>
#include <vector>
#include <sstream>
#include <map>

using mp = map<string, VecPosition>;

class mapPos : public mp {
public:
    void show();

};

class behavior {
private:
    VecPosition me;
    vector<string> viewer;
    mapPos viewThing;
    AngDeg sightAng;
public:
    void parseLine(const string& s);

    void view(const string& s);

    void show();

    void getMySightAng();

    void getMyGlobalPosition();
};

#endif //ROBOCLASS_TASK3_H
