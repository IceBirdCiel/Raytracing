#pragma once

#include "../src/Materials/Material.h"
#include "../src/Objects/Object.h"
#include "../src/Math/Vector.h"
#include "../src/Math/Ray.h"

class Sphere : public Object
{
public:
	Sphere(float rayon, Vector center, Material mat);
	Sphere();
	~Sphere();
	Material getMaterial(const Point& p)const;
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;

private:
	float rayon;
	Material mat;
	Vector center;
};

