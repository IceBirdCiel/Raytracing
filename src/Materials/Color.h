#ifndef __COLOR_CPP__
#define __COLOR_CPP__

struct Color
{
    Color(float r, float g, float b);
    Color() =default;
    Color multiply(const Color& c) const;

    float r = 0;
    float g = 0;
    float b = 0;
};


#endif // __COLOR_CPP