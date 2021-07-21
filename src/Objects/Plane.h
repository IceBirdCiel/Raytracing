#pragma once
#include "../Math/Vector.h"
#include "Object.h"
#include "../Math/Matrix.h"

class Plane : public Object
{
public:
    Plane(Vector pos, Vector rot, Material mat);
    Plane();
    Material getMaterial(const Point& p)const;
    Ray getNormals(const Point& p, const Point& o)const;
    bool intersect(const Ray& ray, Point& impact)const;

private:
    Material mat;
};
