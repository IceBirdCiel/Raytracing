#include "Color.h"
#include <algorithm>
#include <iostream>

Color::Color(float R, float G, float B): r(std::clamp(R, 0.0f, 1.0f)), g(std::clamp(G, 0.0f, 1.0f)), b(std::clamp(B, 0.0f, 1.0f))
{
    std::cout << "New color (" << r << ", " << g << ", " << b << ")" << std::endl;
}

Color Color::multiply(const Color& c) const
{
    float r = this->r * c.r;
    float g = this->g * c.g;
    float b = this->b * c.b;

    return Color(r,g,b);
}

