#pragma once
#include "Object.h"

class Carre : public Object
{
public:
	Carre(Vector pos, Vector rot, float size, float width, float height, Material mat);
	Carre();
	Material getMaterial(const Point& p)const;
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;

private:
	Material mat;
	float width, height;
};
