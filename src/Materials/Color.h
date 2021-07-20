#ifndef __COLOR_CPP__
#define __COLOR_CPP__

struct Color
{
    Color(float r, float g, float b);
    Color() =default;

    float r = 0;
    float g = 0;
    float b = 0;

    Color operator *(const Color& c) const;
    Color operator *(float value) const;
    Color operator +(const Color& c) const;
};


#endif // __COLOR_CPP