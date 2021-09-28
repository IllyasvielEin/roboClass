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

double point::getDistanceTo(point p2) const {
    return sqrt(abs(x-p2.x)*abs(x-p2.x) + abs(y-p2.y)*abs(y-p2.y));
}

point &point::operator-(const point& p1) {
    x -= p1.x;
    y -= p1.y;
    return *this;
}

double point::dotProduct(point p2) const {
    return x*p2.x+y*p2.y;
}

point &point::operator*(double q) {
    x *= q;
    y *= q;
    return *this;
}

point &point::operator+(const point& p1) {
    x += p1.x;
    y += p1.y;
    return *this;
}

point point::cross(point p1p2) const {
    auto e = p1p2; e.normalize();
    auto p1DistancePr = dotProduct(p1p2) / p1p2.getModule();
    auto p1pr = e * p1DistancePr;
    return p1pr;
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


/******************************************************************/
vector<point> linesIntersection(line l1, line l2) {
    /* y = ax + b */
    if (straightLine(l1,l2)) {
        if ( l1.verticalX() && l2.verticalX() ) {
            if (equalDouble(l1.getLine()[0].X(), l2.getLine()[0].X()) ) {
                return vector<point>{point(l1.getLine()[0].X(),0)};
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

int atCircle(line l1, circle c1, point& tmp) {
    int insider = 0;
    int outsider = 0;
    int edge = 0;
    for ( auto p : l1.getPoint() ) {
        if ( p.getDistanceTo(c1.O())<c1.R() ) {
            insider++;
        } else if ( equalDouble(p.getDistanceTo(c1.O()),c1.R()) ) {
            tmp = p;
            edge++;
        } else {
            tmp = p;
            outsider++;
        }
    }
    if ( insider == 2 ) {
        cout << "inside\n";
        return 1;
    } else if ( outsider == 2 ) {
        cout << "outside\n";
        return 2;
    } else if ( insider==1&&outsider==1){
        cout << "str\n";
        return 3;
    } else if ( edge == 1 ){
        return 4;
    } else if ( edge == 2 ) {
        return 5;
    }
    else {
        return -1;
    }
}

vector<point> straightCircleUni(line l1, circle c1, point& tmp) {
    auto p1 = l1.getPoint()[0];
    auto p2 = l1.getPoint()[1];
    auto p1p2 = p2 - p1;
    auto p1o = c1.O() - p1;
    auto e = p1p2; e.normalize();
    auto p1pr = p1o.cross(p1p2);
    auto pr = p1 + p1pr;
    auto ODistancePr = pr.getDistanceTo(c1.O());
    auto half = sqrt(c1.R() * c1.R() - ODistancePr * ODistancePr);
    auto v1 = pr + e * half;
    auto v2 = pr - e * half;

    if ( v1.getDistanceTo(tmp) < v2.getDistanceTo(tmp) ) {
        return {v1};
    } else {
        return {v2};
    }
}

vector<point> interCircle(line l1, circle c1) {

}


vector<point> lineCircleIntersection(line l1, circle c1) {
    point tmp{};
    switch (atCircle(l1,c1,tmp)) {
        case 1: return {};
        case 2: return interCircle(l1,c1);
        case 3: return straightCircleUni(l1,c1,tmp);
        case 4: return {tmp};
        case 5: return {l1.getPoint()};
        case -1:
        {
            cerr << "atCircle() Error.\n";
            return {};
        }
        default: return{};
    }
}

/******************************************************************/
void show(vector<point> pointVec)
{
    if ( !pointVec.empty() ) {
        for ( auto p : pointVec ) {
            p.show();
            cout << " ";
        }
    } else {
        cout << "Empty." << endl;
    }
}

/******************************************************************/