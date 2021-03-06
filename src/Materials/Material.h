#pragma once
#include "Color.h"
#include "../Rendering/Image.h"

class Material
{
public:
    Material(Color a, Color d, Color s, float sh);
    Material();

    Color ambient;
    Color diffuse;
    Color specular;
    float shininess;
    Image* texture;
};


