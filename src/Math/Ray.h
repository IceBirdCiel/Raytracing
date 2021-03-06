#pragma once
#include "Point.h"
#include "Vector.h"

class Ray
{
public:
    Point origin;
    Vector vector;
    Ray(float ox, float oy,float oz, float vx, float vy,float vz);
    Ray(Point o, Vector v);
    Ray();
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
    Ray normalized() const;
};

