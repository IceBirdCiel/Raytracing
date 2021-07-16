#define __MATERIAL_HPP__
#ifdef __MATERIAL_HPP__
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

#endif //__MATERIAL_HPP__
