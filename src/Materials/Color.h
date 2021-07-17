#ifndef __COLOR_CPP__
#define __COLOR_CPP__

class Color
{
public:
    Color(float r, float g, float b);
    Color();
    Color multiply(Color c);

    float operator[](int index) const;

private:
    float m_r;
    float m_g;
    float m_b;
};


#endif // __COLOR_CPP