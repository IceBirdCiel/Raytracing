#pragma once
#include "../Math/Vector.h"
#include "Object.h"
#include "../Math/Matrix.h"

class Plan : public Object
{
public:
    Plan(Vector pos, Vector rot, Material mat);
    Plan();
    Material getMaterial(const Point& p)const;
    Ray getNormals(const Point& p, const Point& o)const;
    bool intersect(const Ray& ray, Point& impact)const;

private:
    Material mat;
};
