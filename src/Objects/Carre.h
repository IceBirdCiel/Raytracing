#pragma once

#include "../Materials/Material.h"
#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

class Carre : public Object
{
public:
	Carre(Vector pos, Vector rot, float scale, Material mat);
	Carre();
	Material getMaterial(const Point& p)const;
	Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;

private:
	Material mat;
};