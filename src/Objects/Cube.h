#pragma once
#include "../Materials/Material.h"
#include "../Math/Vector.h"
#include "Object.h"

class Cube : public Object
{
public:
	Cube(const Vector& pos,const  Vector& rot, const Vector& size,const Material& mat);
	Cube();
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;
	float min(const float a, const float b)const;
	float max(const float a, const float b)const;
    virtual Point getTextureCoordinates(const Point& p) const;
};

