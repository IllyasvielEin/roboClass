//
// Created by Illyasviel on 2021/9/27.
//
#include "task2.h"
/******************************************************************/
point::point(point &&p1) noexcept {
    x = p1.x;
    y = p1.y;
}

void point::setPoint(double _x, double _y) {
    x = _x;
    y = _y;
}

double point::getX() const {
    return x;
}

double point::getY() const {
    return y;
}

void point::show() const {
    printf("point(%.4lf, %.4lf)", x, y);
}

/******************************************************************/

void line::setLine(const point& _p1, const point& _p2) {
    p1 = _p1;
    p2 = _p2;
}

vector<point> line::getLine() {
    return vector<point>{p1, p2};
}

double line::funcY(double X) const {
    if ( !verticalX() ) {
        return X * (Y1()-Y2()) / (X1()-X2()) - (Y1()-Y2()) * X2() / (X1()-X2()) + Y2();
    } else {
        return -11451;
    }
}

double line::funcX(double Y) const {
    if ( !verticalX() ) {
        return (Y -Y2())/ ((Y1()-Y2())/(X1()-X2())) + X2()  ;
    } else {
        return -11451;
    }
}
/******************************************************************/
void circle::setCircle(point _o, double _r) {
    o = _o;
    r = _r;
}

point circle::getO() {
    return o;
}

double circle::getR() const {
    return r;
}
/******************************************************************/
vector<point> linesIntersection(line l1, line l2) {
    /* y = ax + b */
    if (straightLine(l1,l2)) {
        if ( l1.verticalX() && l2.verticalX() ) {
            if (equalDouble(l1.getLine()[0].getX(), l2.getLine()[0].getX()) ) {
                return vector<point>{point(l1.getLine()[0].getX(),0)};
            }
            else {
                return {};
            }
        }
        else if ( l1.verticalX() ) {
            return {point(l1.X1(),l2.funcY(l1.X1()))};
        }
        else if ( l2.verticalX() ) {
            return {point(l2.X1(),l1.funcY(l2.X1()))};
        }
        else {
            return {point(l1.funcX(func2Y(l1,l2)),func2Y(l1,l2))};
        }
    }
    else {
        return {};
    }
}

vector<point> lineCircleIntersection(line l1, circle c1) {

    return {};
}
