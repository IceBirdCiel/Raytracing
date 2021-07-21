#pragma once

#include "../Materials/Material.h"
#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

class Sphere : public Object
{
public:
    Sphere(const Vector& pos, const Vector& rot, const Vector& scale, const Material& mat);
	Sphere();
	[[nodiscard]] Ray getNormals(const Point& p, const Point& o)const override;
	bool intersect(const Ray& ray, Point& impact)const override;
    virtual Point getTextureCoordinates(const Point& p) const;
};

