#pragma once
#include <iostream>
#include <json.hpp>

class Point
{
public:
    Point(float x, float y, float z);
    Point();
    explicit Point(const nlohmann::json& vecData);
    float dot(Point q);

    float operator[](int index)const;
    float& operator[](int index);

    Point operator+(Point q)const;
    Point operator-(Point q)const;
    Point operator*(float r)const;
    Point operator/(float r)const;

    Point operator-()const;

private:
    float m_x;
    float m_y;
    float m_z;
};

std::ostream& operator<<(std::ostream& os, const Point& p);
