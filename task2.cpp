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

double point::dotProduct(point p2) const {
    return x*p2.x+y*p2.y;
}

point point::cross(point p1p2) const {
    auto e = p1p2; e.normalize();
    auto p1DistancePr = dotProduct(p1p2) / p1p2.getModule();
    auto p1pr = e * p1DistancePr;
    return p1pr;
}

point point::operator+(const point &p1) {
    auto tmp = *this;
    tmp.x += p1.x;
    tmp.y += p1.y;
    return tmp;
}

point point::operator-(const point &p1) {
    auto tmp = *this;
    tmp.x -= p1.x;
    tmp.y -= p1.y;
    return tmp;
}

point point::operator*(const double &q) {
    auto tmp = *this;
    tmp.x *= q;
    tmp.y *= q;
    return tmp;
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
    auto a = (Y1()-Y2()) / ( X1()-X2() );
    if ( !verticalX() ) {
        cout << a << endl;
        return (Y-Y2()+ a*X2() ) / a ;
    } else {
        return -11451;
    }
}
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
            return {point(func2X(l1,l2), l1.funcY(func2X(l1,l2)))};
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
            p.show();
            printf("is inside.\n");
            insider++;
        } else if ( equalDouble(p.getDistanceTo(c1.O()),c1.R()) ) {
            tmp = p;
            p.show();
            printf("is at the edge.\n");
            edge++;
        } else {
            tmp = p;
            p.show();
            printf("is outside.\n");
            outsider++;
        }
    }
    if ( insider == 2 ) {
        return 1;
    } else if ( outsider == 2 ) {
        return 2;
    } else if ( insider==1&&outsider==1){
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
    auto p1pr = p1o.cross(p1p2);
    auto pr = p1 + p1pr;
    auto e = p1p2;
    e.normalize();
    auto ODistancePr = pr.getDistanceTo(c1.O());
    auto half = sqrt(pow(c1.R(), 2) - pow(ODistancePr,2));
    auto v1 = pr + e * half;
    auto v2 = pr - e * half;
    if ( v1.getDistanceTo(tmp) < v2.getDistanceTo(tmp) ) {
        return {v1};
    } else {
        return {v2};
    }
}

vector<point> interCircle(line l1, circle c1) {
    auto p1 = l1.getPoint()[0];
    auto p2 = l1.getPoint()[1];
    auto p1p2 = p2 - p1;
    auto p1o = c1.O() - p1;
    auto p1pr = p1o.cross(p1p2);
    auto pr = p1 + p1pr;
    auto e = p1p2;
    e.normalize();
    auto ODistancePr = pr.getDistanceTo(c1.O());
    auto half = sqrt(pow(c1.R(), 2) - pow(ODistancePr,2));
    auto v1 = pr + e * half;
    auto v2 = pr - e * half;
    return {v1, v2};
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

void show(const vector<point>& pointVec)
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
rectangle::rectangle(const rectangle& ra1) {
    points = ra1.points;
}

rectangle::rectangle(rectangle&& ra1)  noexcept {
    points = ra1.points;
}

vector<point> lineRectangleIntersection(line l1, rectangle ra1) {
    withRectangle(l1.getPoint()[0], ra1);
    withRectangle(l1.getPoint()[1], ra1);
    vector<point> ans;
    auto lineVec = ra1.getline();
    for ( auto l : lineVec ) {
        auto tmp = linesIntersection(l, l1);
        if ( !tmp.empty() ) {
            ans.push_back( tmp[0] );
        }
    }
    return ans;
}

vector<line> rectangle::getline() {
    vector<line> ans;
    ans.reserve(4);
    for (int i = 0; i < 4; ++i) {
        auto next = i+1;
        if ( i==3 )
        {
            next = 0;
        }
        ans.emplace_back(points[i], points[next] );
    }
//    for ( auto l : ans ) {
//        l.show();
//    }
    return ans;
}

double rectangle::getMaxX() {
    auto max = -1.0;
    for ( auto p : points ) {
        if ( p.X()>max ) {
            max = p.X();
        }
    }
    return max;
}

double rectangle::getMinX() {
    auto min = 999.0;
    for ( auto p : points ) {
        if ( p.X()<min ) {
            min = p.X();
        }
    }
    return min;
}

double rectangle::getMaxY() {
    auto max = -1.0;
    for ( auto p : points ) {
        if ( p.Y()>max ) {
            max = p.Y();
        }
    }
    return max;
}

double rectangle::getMinY() {
    auto min = 999.0;
    for ( auto p : points ) {
        if ( p.Y()<min ) {
            min = p.Y();
        }
    }
    return min;
}

bool samePoint(point p1, point p2) {
    if (equalDouble(p1.X(), p2.X()) && equalDouble(p1.Y(), p2.Y())) {
        return true;
    } else {
        return false;
    }
}

bool atRectangle(point p1, rectangle ra1) {
    bool flag = false;
    any_of(ra1.getPoints().begin(), ra1.getPoints().end(), [&flag,p1](point p) {
        flag = true;
        return p.X()==p1.X()&&p.Y()==p1.Y();
    });
    return flag;
}

bool withRectangle(point p1, rectangle ra1) {
    if ( p1.X()>ra1.getMinX()&&p1.X()<ra1.getMaxX()&&p1.Y()>ra1.getMinY()&&p1.Y()<ra1.getMaxY()) {
        p1.show();
        printf("is in rectangle\n");
        return true;
    } else if (atRectangle(p1, ra1)) {
        p1.show();
        printf("is at the edge of rectangle\n");
    } else {
        p1.show();
        printf("is not in rectangle\n");
        return false;
    }
}

