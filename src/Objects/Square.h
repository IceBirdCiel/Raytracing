#pragma once

#include "../Materials/Material.h"
#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

class Square : public Object
{
public:
	Square(const Vector& pos,const  Vector& rot, float scale,const  Material& mat);
	Square();
	Material getMaterial(const Point& p)const;
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;

private:
	Material mat;
};