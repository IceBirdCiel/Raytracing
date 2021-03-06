#pragma once
#include "../Math/Vector.h"
#include "Object.h"
#include "../Math/Matrix.h"

class Plane : public Object
{
public:
    Plane(Vector pos, Vector rot, Vector scale, Material mat);
    Plane();
    Ray getNormals(const Point& p, const Point& o)const;
    bool intersect(const Ray& ray, Point& impact)const;
    virtual Point getTextureCoordinates(const Point& p) const;
};
