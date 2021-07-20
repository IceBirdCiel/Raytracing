#pragma once
#include "../Materials/Material.h"
#include "../Math/Vector.h"
#include "Object.h"

class Cube : public Object
{
public:
	Cube(Vector pos, Vector rot, float size, Material mat);
	Cube();
	Material getMaterial(const Point& p)const;
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;
	float min(const float a, const float b)const;
	float max(const float a, const float b)const;

private:
	Material mat;
};

