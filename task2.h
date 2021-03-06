//
// Created by Illyasviel on 2021/9/27.
//
#ifndef ROBOCLASS_TASK2_H
#define ROBOCLASS_TASK2_H
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class point {
private:
    double x;
    double y;

public:
    friend class line;

    point& operator=(const point& p1) = default;

    point operator+(const point& p1);

    point operator-(const point& p1);

    point operator*(const double& q);

    point() = default;

    point(double _x, double _y) : x(_x), y(_y) {}

    point(const point& p1) = default;

    point(point&& p1) noexcept ;

    void setPoint(double _x, double _y);

    inline double X() const {
        return x;
    }

    inline double Y() const {
        return y;
    }

    inline string show() const {
        printf("point(%lf, %lf) ", x, y);
        return {"point("+to_string(x)+" ,"+to_string(y)+")"};
    }

    double getDistanceTo(point p2) const;

    inline double getModule() const {
        return ( sqrt(x*x+y*y) );
    }

    inline void normalize() {
        if ( getModule() > 0.001 ) {
            auto module = getModule();
            x /= module;
            y /= module;
        }
    }

    double dotProduct(point p2) const;

    point cross(point p1p2) const;
};

class circle;
class line  {
private:
    point p1;
    point p2;

public:
    friend class circle;

    line& operator=(const line& l1) = default;

    line() = default;

    line(point _p1, point _p2) : p1(move(_p1)), p2(move(_p2)) {}

    line(double x1, double y1, double x2, double y2) : p1(move(point(x1, y1))), p2(move(point(x2, y2))) {}

    void setLine(const point& _p1, const point& _p2);

    vector<point> getLine();

    inline bool verticalX() const {
       return p1.x == p2.x;
    }

    inline double X1() const {
        return p1.x;
    }
    inline double Y1() const {
        return p1.y;
    }
    inline double X2() const {
        return p2.x;
    }
    inline double Y2() const {
        return p2.y;
    }

     inline double getMinX() const {
         return p1.x < p2.x?p1.x:p2.x;
     }

    double getMaxX() const {
        return p1.x > p2.x?p1.x:p2.x;
    }

    double getMinY() const {
        return p1.y < p2.y?p1.y:p2.y;
    }

    double getMaxY() const {
        return p1.y > p2.y?p1.y:p2.y;
    }

    inline vector<point> getPoint() {
        return {p1, p2};
    }

    double funcY(double X) const;

    double funcX(double Y) const;

    inline void show() {
        getPoint()[0].show();
        printf("to ");
        getPoint()[1].show();
        cout << endl;
    }
};

class circle {
private:
    point o;
    double r;

public:
    circle& operator=(const circle& o1) = default;

    circle() = default;

    circle(point _o, double _r) : o(move(_o)), r(_r) {}

    inline void setCircle(point _o, double _r) {
        o = _o;
        r = _r;
    }

    inline point O() {
        return o;
    }

    inline double R() const {
        return r;
    }
};

class rectangle {
private:
    vector<point> points;

public:
    rectangle& operator=(const rectangle& ra1) = default;

    rectangle() = default;

    rectangle(initializer_list<point> il1) : points(il1) {};

    explicit rectangle(vector<point> v1) : points(move(v1)) {};

    rectangle(const rectangle& ra1);

    rectangle(rectangle&& ra1) noexcept;

    vector<line> getline();

    inline vector<point> getPoints()  {
        return points;
    }

    double getMaxX();

    double getMinX();

    double getMaxY();

    double getMinY();
};

/******************************************************************/
vector<point> linesIntersection(line l1, line l2);

vector<point> lineCircleIntersection(line l1, circle c1);

vector<point> lineRectangleIntersection(line l1, rectangle ra1);

void show(const vector<point>& pointVec);

bool withRectangle(point p1, rectangle ra1);
/******************************************************************/
inline double mult(point a, point b, point c) {
    return (a.X()-c.X())*(b.Y()-c.Y()) - (b.X()-c.X())*(a.Y()-c.Y());
}

inline bool straightLine(line& l1, line& l2) {
    return l1.getMaxX()>=l2.getMinX()&&l1.getMaxY()>=l2.getMinY()
        && l2.getMaxX()>=l1.getMinX()&&l2.getMaxY()>=l1.getMinY()
        && mult(l2.getPoint()[0], l1.getPoint()[1], l1.getPoint()[0]) *
            mult(l1.getPoint()[1], l2.getPoint()[1], l1.getPoint()[0]) >= 0
        && mult(l1.getPoint()[0], l2.getPoint()[1], l2.getPoint()[0]) *
            mult(l2.getPoint()[1], l1.getPoint()[1], l2.getPoint()[0]) >= 0;
}

inline bool equalDouble(double d1, double d2) {
    return abs(d1-d2) < 0.001;
}

inline double func2X(line l1, line l2) {
    auto a1 = (l1.Y1()-l1.Y2())/(l1.X1()-l1.X2());
    auto a2 = (l2.Y1()-l2.Y2())/(l2.X1()-l2.X2());
    return ( a1*l1.X2() - a2*l2.X2() - l1.Y2() + l2.Y2() ) / (a1-a2);
}
/******************************************************************/
#endif //ROBOCLASS_TASK2_H
