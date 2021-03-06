#include "Vector.h"
#include <cmath>

float Vector::norm() const
{
    return sqrt(m_x*m_x + m_y * m_y + m_z * m_z);
}

Vector Vector::normalized() const
{
    float norm = Vector::norm();

    return Vector(m_x/norm, m_y / norm, m_z / norm);
}

Vector Vector::cross(Vector v) const
{
    float x = m_y * v[2] - v[1] * m_z;
    float y = m_z * v[0] - v[2] * m_x;
    float z = m_x * v[1] - v[0] * m_y;
    return Vector(x, y, z);
}

float Vector::dot(Vector v) const
{
    return m_x*v[0] + m_y * v[1] + m_z * v[2];
}

Vector Vector::reflect(const Vector& v)const{
    return v - (*this) * (2 * v.dot((*this)));
}

float Vector::operator[](int index) const
{
    if (index == 0) return m_x;
    if (index == 1) return m_y;
    if (index == 2) return m_z;
    throw "Index out of range";
}

float& Vector::operator[](int index)
{
    if (index == 0) return m_x;
    if (index == 1) return m_y;
    if (index == 2) return m_z;
    throw "Index out of range";
}

Vector Vector::operator+(Vector v) const
{
    return Vector(m_x + v[0], m_y + v[1], m_z + v[2]);
}

Vector Vector::operator-(Vector v) const
{
    return Vector(m_x - v[0], m_y - v[1], m_z - v[2]);
}

Vector Vector::operator-() const
{
    return Vector(-m_x, -m_y, -m_z);
}

Vector Vector::operator/(float value) const
{
    return Vector(m_x / value, m_y / value, m_z / value);
}

Vector Vector::operator*(float value) const
{
    return Vector(m_x * value, m_y * value, m_z * value);
}

Vector& Vector::operator=(const Point& p) {
    m_x = p[0];
    m_y = p[1];
    m_z = p[2];
    return (*this);
}

Vector::Vector(const nlohmann::json &vecData) {
    (*this)[0] = vecData[0];
    (*this)[1] = vecData[1];
    (*this)[2] = vecData[2];
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

Point operator+(Point p, Vector v) {

    return Point(p[0] + v[0], p[1] + v[1], p[2] + v[2]);
}
