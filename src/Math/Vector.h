#pragma once
#include <iostream>
#include <json.hpp>
#include "Point.h"

class Vector
{
public:
    Vector(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {

    }
    explicit Vector(const nlohmann::json& vecData);
    Vector() : m_x(0), m_y(0), m_z(0) {}
    Vector(const Point& p) : m_x(p[0]), m_y(p[1]), m_z(p[2]){

    }

    float norm() const;
    Vector normalized() const;
    Vector cross(Vector v) const;
    float dot(Vector v) const;
    Vector reflect(const Vector& v)const;

    float operator [](int index) const;
    float& operator [](int index);
    Vector operator +(Vector v) const;   // value = vector1+vector2
    Vector operator -(Vector v) const;   // value = vector1-vector2
    Vector operator -() const;           // value = -vector
    Vector operator /(float value) const;// value = vector/float
    Vector operator *(float value) const;// value = vector*float
    Vector& operator =(const Point& p);

private:
    float m_x;
    float m_y;
    float m_z;
};
std::ostream& operator<<(std::ostream& os, const Vector& v);
Point operator+(Point p, Vector v);

