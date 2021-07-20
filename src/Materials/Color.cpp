#include "Color.h"
#include <algorithm>

Color::Color(float R, float G, float B) : r(std::clamp(R, 0.0f, 1.0f)), g(std::clamp(G, 0.0f, 1.0f)), b(std::clamp(B, 0.0f, 1.0f))
{
}

Color Color::operator*(float value) const {
    return Color(r*value,g*value,b*value);
}

Color Color::operator*(const Color& c) const {
    return Color(r*c.r,g*c.g,b*c.b);
}

Color Color::operator+(const Color& c) const {
    return Color(r + c.r, g + c.g, b + c.b);
}
