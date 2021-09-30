//
// Created by Illyasviel on 2021/9/30.
//
#include "task3.h"

/***********************************************************/

mp pos {
    make_pair("C",VecPosition(0,0)),
    make_pair("P1",VecPosition(-52.5,-32)),
    make_pair("P2", VecPosition(-52.5, 32)),
    make_pair("P3", VecPosition(52.5,32)) ,
    make_pair("P4", VecPosition(52.5,-32)),
    make_pair("P5", VecPosition(0,-32)),
    make_pair("p6", VecPosition(0,32)),
    make_pair("P7",VecPosition(-30,-7)),
    make_pair("P8", VecPosition(-30, 7)) ,
    make_pair("P9", VecPosition(30,7)),
    make_pair("P10", VecPosition(30, -7)),
    make_pair("G1", VecPosition(-52.5,0)),
    make_pair("G2", VecPosition(52.5,0))
};

/***********************************************************/
void mapPos::show() {
    for ( const auto& m : *this ) {
        printf("%s (%lf, %lf)   ", m.first.c_str(), m.second.getX(), m.second.getY());
    }
}
/***********************************************************/

void behavior::parseLine(const string &s) {
    string ins;
    for ( auto l : s ) {
        if ( l != '(' && l != ')' ) {
            ins.push_back(l);
        } else if ( l == ')' ) {
            view(ins);
            ins.clear();
        }
    }
}

void behavior::view(const string &s) {
    istringstream iss(s);
    string tmpString;
    double t_dMag;
    double t_ang;
    iss >> tmpString;
    iss >> t_dMag;
    iss >> t_ang;
//    cout << t_dMag << " " << t_ang << endl;
    viewer.push_back(tmpString);
    viewThing[tmpString]=VecPosition(t_dMag, t_ang);
}

void behavior::show() {
    viewThing.show();
    printf("\n");
}

void behavior::getMySightAng() {

}

void behavior::getMyGlobalPosition() {

}
/***********************************************************/


