#pragma once
#include "Color.h"

class Material
{
public:
    Material(Color a, Color d, Color s, float sh);
    Material();

    Color ka;
    Color kd;
    Color ks;
    float shininess;
};


