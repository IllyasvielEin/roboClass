#include "vecposition.h"
#include <cstdio>    // needed for sprintf

int sign(double d1) {
    return (d1 > 0) ? 1 : -1;
}

double max(double d1, double d2) {
    return (d1 > d2) ? d1 : d2;
}

double min(double d1, double d2) {
    return (d1 < d2) ? d1 : d2;
}

AngDeg Rad2Deg(AngRad x) {
    return (x * 180 / M_PI);
}

AngRad Deg2Rad(AngDeg x) {
    return (x * M_PI / 180);
}

double cosDeg(AngDeg x) {
    return (cos(Deg2Rad(x)));
}

double sinDeg(AngDeg x) {
    return (sin(Deg2Rad(x)));
}

double tanDeg(AngDeg x) {
    return (tan(Deg2Rad(x)));
}

AngDeg atanDeg(double x) {
    return (Rad2Deg(atan(x)));
}

double atan2Deg(double x, double y) {
    if (fabs(x) < EPSILON && fabs(y) < EPSILON)
        return (0.0);

    return Rad2Deg(atan2(x, y));
}

AngDeg acosDeg(double x) {
    if (x >= 1)
        return (0.0);
    else if (x <= -1)
        return (180.0);

    return (Rad2Deg(acos(x)));
}

AngDeg asinDeg(double x) {
    if (x >= 1)
        return (90.0);
    else if (x <= -1)
        return (-90.0);

    return (Rad2Deg(asin(x)));
}

bool isAngInInterval(AngDeg ang, AngDeg angMin, AngDeg angMax) {
    if ((ang + 360) < 360) ang += 360;
    if ((angMin + 360) < 360) angMin += 360;
    if ((angMax + 360) < 360) angMax += 360;

    if (angMin < angMax)
        return angMin < ang && ang < angMax;
    else
        return !(angMax < ang && ang < angMin);
}

AngDeg getBisectorTwoAngles(AngDeg angMin, AngDeg angMax) {
    return VecPosition::normalizeAngle(
            atan2Deg((sinDeg(angMin) + sinDeg(angMax)) / 2.0,
                     (cosDeg(angMin) + cosDeg(angMax)) / 2.0));
}

VecPosition::VecPosition(double x, double y, CoordSystemT cs) {
    setVecPosition(x, y, cs);
}

VecPosition VecPosition::operator-() const {
    return {-m_x, -m_y};
}

VecPosition VecPosition::operator+(const double &d) const {
    return {m_x + d, m_y + d};
}

VecPosition VecPosition::operator+(const VecPosition &p) const {
    return {m_x + p.m_x, m_y + p.m_y};
}

VecPosition VecPosition::operator-(const double &d) const {
    return {m_x - d, m_y - d};
}

VecPosition VecPosition::operator-(const VecPosition &p) const {
    return {m_x - p.m_x, m_y - p.m_y};
}

VecPosition VecPosition::operator*(const double &d) const {
    return {m_x * d, m_y * d};
}

VecPosition VecPosition::operator*(const VecPosition &p) const {
    return {m_x * p.m_x, m_y * p.m_y};
}

VecPosition VecPosition::operator/(const double &d) const {
    return {m_x / d, m_y / d};
}

VecPosition VecPosition::operator/(const VecPosition &p) const {
    return {m_x / p.m_x, m_y / p.m_y};
}

VecPosition& VecPosition::operator=(const double &d) {
    m_x = d;
    m_y = d;
    return *this;
}

void VecPosition::operator+=(const VecPosition &p) {
    m_x += p.m_x;
    m_y += p.m_y;
}

void VecPosition::operator+=(const double &d) {
    m_x += d;
    m_y += d;
}

void VecPosition::operator-=(const VecPosition &p) {
    m_x -= p.m_x;
    m_y -= p.m_y;
}

void VecPosition::operator-=(const double &d) {
    m_x -= d;
    m_y -= d;
}

void VecPosition::operator*=(const VecPosition &p) {
    m_x *= p.m_x;
    m_y *= p.m_y;
}

void VecPosition::operator*=(const double &d) {
    m_x *= d;
    m_y *= d;
}

void VecPosition::operator/=(const VecPosition &p) {
    m_x /= p.m_x;
    m_y /= p.m_y;
}

void VecPosition::operator/=(const double &d) {
    m_x /= d;
    m_y /= d;
}

bool VecPosition::operator!=(const VecPosition &p) const {
    return ((m_x != p.m_x) || (m_y != p.m_y));
}

bool VecPosition::operator!=(const double &d) const {
    return ((m_x != d) || (m_y != d));
}

bool VecPosition::operator==(const VecPosition &p) const {
    return ((m_x == p.m_x) && (m_y == p.m_y));
}

bool VecPosition::operator==(const double &d) const {
    return ((m_x == d) && (m_y == d));
}

ostream &operator<<(ostream &os, VecPosition v) {
    return (os << "( " << v.m_x << ", " << v.m_y << " )");
}

void VecPosition::show(CoordSystemT cs) {
    if (cs == CARTESIAN)
        cout << *this << endl;
    else
        cout << "( r: " << getMagnitude() << ", phi: " << getDirection() << "  )";
}

bool VecPosition::setX(double dX) {
    m_x = dX;
    return (true);
}

double VecPosition::getX() const {
    return (m_x);
}

bool VecPosition::setY(double dY) {
    m_y = dY;
    return (true);
}

double VecPosition::getY() const {
    return (m_y);
}

void VecPosition::setVecPosition(double dX, double dY, CoordSystemT cs) {
    if (cs == CARTESIAN) {
        m_x = dX;
        m_y = dY;
    } else
        *this = getVecPositionFromPolar(dX, dY);
}

double VecPosition::getDistanceTo(const VecPosition p) const {
    return ((*this - p).getMagnitude());
}

VecPosition VecPosition::setMagnitude(double d) {
    if (getMagnitude() > EPSILON)
        (*this) *= (d / getMagnitude());

    return (*this);
}

double VecPosition::getMagnitude() const {
    return (sqrt(m_x * m_x + m_y * m_y));
}

AngDeg VecPosition::getDirection() const {
    return (atan2Deg(m_y, m_x));
}

bool VecPosition::isInFrontOf(const VecPosition &p) const {
    return (m_x > p.getX());
}

bool VecPosition::isInFrontOf(const double &d) const {
    return (m_x > d);
}

bool VecPosition::isBehindOf(const VecPosition &p) const {
    return (m_x < p.getX());
}

bool VecPosition::isBehindOf(const double &d) const {
    return (m_x < d);
}

bool VecPosition::isLeftOf(const VecPosition &p) const {
    return (m_y < p.getY());
}

bool VecPosition::isLeftOf(const double &d) const {
    return (m_y < d);
}

bool VecPosition::isRightOf(const VecPosition &p) const {
    return (m_y > p.getY());
}

bool VecPosition::isRightOf(const double &d) const {
    return (m_y > d);
}

bool VecPosition::isBetweenX(const VecPosition &p1, const VecPosition &p2) const {
    return (isInFrontOf(p1) && isBehindOf(p2));
}

bool VecPosition::isBetweenX(const double &d1, const double &d2) const {
    return (isInFrontOf(d1) && isBehindOf(d2));
}

bool VecPosition::isBetweenY(const VecPosition &p1, const VecPosition &p2) const {
    return (isRightOf(p1) && isLeftOf(p2));
}

bool VecPosition::isBetweenY(const double &d1, const double &d2) const {
    return (isRightOf(d1) && isLeftOf(d2));
}

VecPosition VecPosition::normalize() {
    return (setMagnitude(1.0));
}

VecPosition VecPosition::rotate(AngDeg angle) {
    double dMag = this->getMagnitude();
    double dNewDir = this->getDirection() + angle;
    setVecPosition(dMag, dNewDir, POLAR);
    return (*this);
}

VecPosition VecPosition::globalToRelative(VecPosition origin, AngDeg ang) {
    *this -= origin;
    return (rotate(-ang));
}

VecPosition VecPosition::relativeToGlobal(VecPosition origin, AngDeg ang) {
    rotate(ang);
    *this += origin;
    return (*this);
}

VecPosition VecPosition::getVecPositionOnLineFraction(VecPosition &p,
                                                      double dFrac) {
    return ((*this) * (1.0 - dFrac) + (p * dFrac));
}

VecPosition VecPosition::getVecPositionFromPolar(double dMag, AngDeg ang) {
    // cos(phi) = x/r <=> x = r*cos(phi); sin(phi) = y/r <=> y = r*sin(phi)
    return {dMag * cosDeg(ang), dMag * sinDeg(ang)};
}

VecPosition VecPosition::getVecPositionFromPolar(const VecPosition& v1) {
    /* v1(dMag, ang) */
    return {v1.m_x*cos(v1.m_y),  v1.m_x*sin(v1.m_y)};
}

AngDeg VecPosition::normalizeAngle(AngDeg angle) {
    while (angle > 180.0) angle -= 360.0;
    while (angle < -180.0) angle += 360.0;

    return (angle);
}
