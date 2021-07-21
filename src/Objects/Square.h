#pragma once

#include "../Materials/Material.h"
#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

class Square : public Object
{
public:
	Square(const Vector& pos,const  Vector& rot, const Vector& scale,const  Material& mat);
	Square();
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;

};