#pragma once
#include "Entity.h"
#include "../Materials/Color.h"
#include "../Math/Ray.h"
#include "../Math/Point.h"
#include "../Math/Vector.h"

class Light: public Entity
{
public:
    Light(Vector pos, Vector rot, float scale, Color a, Color d, Color s);
    Ray getRayToLight(const Point& p)const;
    Ray getRayFromLight(const Point& p)const;
    Vector getVectorToLight(const Point& p)const;
    Vector getVectorFromLight(const Point& p)const;

    Color ambient;
    Color diffuse;
    Color specular;

private:
    Matrix trans;
    Matrix transInv;
};



