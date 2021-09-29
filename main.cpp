//
// Created by Illyasviel on 2021/9/27.
//
//#include "task1.h"
#include "task2.h"

int main() {
//    line l1(point(3,2), point(1,0));
//    line l2(point(3,-1), point(2,2));
//    auto pointVec = linesIntersection(l1, l2);
//    if ( !pointVec.empty() ) {
//        pointVec[0].show();
//    } else {
//        cout << "Empty." << endl;
//    }

//    line l1(3,0,0,3);
//    circle c1(point(1,1), 1);
//    auto pointVec = lineCircleIntersection(l1,c1);
//    printf("the intersections is as followed: ");
//    show(pointVec);

    rectangle ra1({point(1,3), point(4,3), point(4,1), point(1,1)});
    line l1(2,3.5,5.5,0);
    auto ans = lineRectangleIntersection(l1, ra1);
    show(ans);

    return 0;
}
