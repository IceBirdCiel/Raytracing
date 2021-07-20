#pragma once

#include "../Materials/Material.h"
#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

class Sphere : public Object
{
public:
    Sphere(Vector pos, Vector rot, float scale, Material mat);
	Sphere();
    [[nodiscard]] Material getMaterial(const Point& p)const override;
	[[nodiscard]] Ray getNormals(const Point& p, const Point& o)const override;
	bool intersect(const Ray& ray, Point& impact)const override;

private:
	Material mat;
};

