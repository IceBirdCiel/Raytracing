#pragma once
#include "Entity.h"
#include "Color.h"
#include "Ray.h"
#include "Point.h"
#include "Vector.h"

class Light: public Entity
{
public:
	Light(Vector pos, Vector rot, Vector s);
	Light();
	Ray getRayToLight(const Point& p)const;
	Ray getRayFromLight(const Point& p)const;
	Vector getVectorToLight(const Point& p)const;
	Vector getVectorFromLight(const Point& p)const;

	Color id;
	Color is;

private:
	Vector position;
	Vector rotation;
	Vector size;
};



