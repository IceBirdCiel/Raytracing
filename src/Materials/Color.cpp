#include "Color.h"

Color::Color(float r, float g, float b): m_r(r), m_g(g), m_b(b)
{
    m_r = (m_r > 1) ? 1 : (m_r < 0) ? 0 : m_r;
    m_g = (m_g > 1) ? 1 : (m_g < 0) ? 0 : m_g;
    m_b = (m_b > 1) ? 1 : (m_b < 0) ? 0 : m_b;
}

Color::Color(): m_r(0), m_g(0), m_b(0){}

Color Color::multiply(Color c)
{
    float r = this->m_r * c.m_r;
    float g = this->m_g * c.m_g;
    float b = this->m_b * c.m_b;

    return Color(r,g,b);
}

float Color::operator[](int index) const
{
    if (index == 0) return m_r;
    if (index == 1) return m_g;
    if (index == 2) return m_b;
    throw "Index out of range";
}

