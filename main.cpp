//
// Created by Illyasviel on 2021/9/27.
//
//#include "task1.h"
#include "task2.h"

int main() {
    line l1(point(3,2), point(1,0));
    line l2(point(3,-1), point(2,2));
    auto pointVec = linesIntersection(l1, l2);
    if ( !pointVec.empty() ) {
        pointVec[0].show();
    } else {
        cout << "Empty." << endl;
    }

    return 0;
}
