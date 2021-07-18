#include "Point.h"

Point::Point(float x, float y, float z): m_x(x), m_y(y), m_z(z){}

Point::Point() : m_x(0), m_y(0), m_z(0){}

float Point::dot(Point q)
{
    float res = this->m_x * q.m_x
                + this->m_y * q.m_y
                + this->m_z * q.m_z;

    return res;
}

float Point::operator[](int index) const
{
    if (index == 0) return m_x;
    if (index == 1) return m_y;
    if (index == 2) return m_z;
    throw "Index out of range";
}

float& Point::operator[](int index)
{
    if (index == 0) return m_x;
    if (index == 1) return m_y;
    if (index == 2) return m_z;
    throw "Index out of range";
}


Point Point::operator+(Point q)const
{
    float x = this->m_x + q.m_x;
    float y = this->m_y + q.m_y;
    float z = this->m_z + q.m_z;

    return Point(x,y,z);
}

Point Point::operator-(Point q)const
{
    float x = this->m_x - q.m_x;
    float y = this->m_y - q.m_y;
    float z = this->m_z - q.m_z;

    return Point(x,y,z);
}

Point Point::operator*(float r)const
{
    float x = this->m_x * r;
    float y = this->m_y * r;
    float z = this->m_z * r;

    return Point(x, y, z);
}

Point Point::operator/(float r)const
{
    float x = this->m_x / r;
    float y = this->m_y / r;
    float z = this->m_z / r;

    return Point(x, y, z);
}

Point Point::operator-()const
{
    return Point(-m_x,-m_y,-m_z);
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    return os << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")";
}