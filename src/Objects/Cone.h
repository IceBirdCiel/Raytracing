#pragma once

#include "../Materials/Material.h"
#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Ray.h"

class Cone : public Object {
public:
	Cone(const Vector& pos, const Vector& rot, const Vector& scale, Material mat);
	Cone();
	[[nodiscard]] Ray getNormals(const Point& p, const Point& o)const;
	bool intersect(const Ray& ray, Point& impact)const;
	virtual Point getTextureCoordinates(const Point& p) const;
};