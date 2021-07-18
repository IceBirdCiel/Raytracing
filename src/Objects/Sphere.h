#pragma once

#include "../Materials/Material.h"
#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

class Sphere : public Object
{
public:
	Sphere(float rayon, Vector center, Material mat);
	Sphere();
	Material getMaterial(const Point& p)const;
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;

private:
	float rayon;
	Material mat;
	Vector center;
};

