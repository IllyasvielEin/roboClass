#ifndef _GEOMETRY_
#define _GEOMETRY_

#include <cmath>       // needed for M_PI constant
#include <string>       // needed for string
#include <iostream>

using namespace std;

typedef double AngRad;
typedef double AngDeg;

#define EPSILON 0.0001

double max(double d1, double d2);

double min(double d1, double d2);

int sign(double d1);

AngDeg Rad2Deg(AngRad x);

AngRad Deg2Rad(AngDeg x);

double cosDeg(AngDeg x);

double sinDeg(AngDeg x);

double tanDeg(AngDeg x);

AngDeg atanDeg(double x);

double atan2Deg(double x, double y);

AngDeg acosDeg(double x);

AngDeg asinDeg(double x);

bool isAngInInterval(AngDeg ang, AngDeg angMin, AngDeg angMax);

AngDeg getBisectorTwoAngles(AngDeg angMin, AngDeg angMax);

enum CoordSystemT {
    CARTESIAN,
    POLAR
};

class VecPosition {
private:

    double m_x{};
    double m_y{};

public:
    VecPosition(double vx = 0,
                double vy = 0,
                CoordSystemT cs = CARTESIAN);

    VecPosition operator-() const;

    VecPosition operator+(const double &d) const;

    VecPosition operator+(const VecPosition &p) const;

    VecPosition operator-(const double &d) const;

    VecPosition operator-(const VecPosition &p) const;

    VecPosition operator*(const double &d) const;

    VecPosition operator*(const VecPosition &p) const;

    VecPosition operator/(const double &d) const;

    VecPosition operator/(const VecPosition &p) const;

    VecPosition & operator=(const double &d);

    void operator+=(const VecPosition &p);

    void operator+=(const double &d);

    void operator-=(const VecPosition &p);

    void operator-=(const double &d);

    void operator*=(const VecPosition &p);

    void operator*=(const double &d);

    void operator/=(const VecPosition &p);

    void operator/=(const double &d);

    bool operator!=(const VecPosition &p) const;

    bool operator!=(const double &d) const;

    bool operator==(const VecPosition &p) const;

    bool operator==(const double &d) const;

    // methods for producing output
    friend ostream &operator<<(ostream &os,
                               VecPosition p);

    void show(CoordSystemT cs = CARTESIAN);

    bool setX(double dX);

    double getX() const;

    bool setY(double dY);

    double getY() const;

    void setVecPosition(double dX = 0,
                        double dY = 0,
                        CoordSystemT cs = CARTESIAN);

    double getDistanceTo(VecPosition p) const;

    VecPosition setMagnitude(double d);

    double getMagnitude() const;

    AngDeg getDirection() const;

    bool isInFrontOf(const VecPosition &p) const;

    bool isInFrontOf(const double &d) const;

    bool isBehindOf(const VecPosition &p) const;

    bool isBehindOf(const double &d) const;

    bool isLeftOf(const VecPosition &p) const;

    bool isLeftOf(const double &d) const;

    bool isRightOf(const VecPosition &p) const;

    bool isRightOf(const double &d) const;

    bool isBetweenX(const VecPosition &p1,
                    const VecPosition &p2) const;

    bool isBetweenX(const double &d1,
                    const double &d2) const;

    bool isBetweenY(const VecPosition &p1,
                    const VecPosition &p2) const;

    bool isBetweenY(const double &d1,
                    const double &d2) const;

    VecPosition normalize();

    VecPosition rotate(AngDeg angle);

    VecPosition globalToRelative(VecPosition orig,
                                 AngDeg ang);

    VecPosition relativeToGlobal(VecPosition orig,
                                 AngDeg ang);

    VecPosition getVecPositionOnLineFraction(VecPosition &p,
                                             double dFrac);

    static VecPosition getVecPositionFromPolar(double dMag,
                                               AngDeg ang);

    VecPosition getVecPositionFromPolar(const VecPosition& v);

    static AngDeg normalizeAngle(AngDeg angle);
};

#endif
