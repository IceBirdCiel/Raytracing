#pragma once

#include "../Math/Vector.h"
#include "Object.h"
#include "../Math/Matrix.h"

class Cylinder : public Object
{
public:
    Cylinder(const Vector& pos, const Vector& rot, const Vector& scale, Material mat);
    Cylinder();
    Ray getNormals(const Point& p, const Point& o)const;
    bool intersect(const Ray& ray, Point& impact)const;

};
