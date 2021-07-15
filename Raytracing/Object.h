#define __OBJECT_HPP__
#ifdef __OBJECT_HPP__
#include "Entity.h"
#include "Material.h"
#include "Ray.h"

template<typename T>
class Object : public Entity
{
public:
	Material getMaterial(const Point& p)const;
	Ray getNormal(const Point& p)const;
	bool intersect(const Ray& ray, Point& impact)const;

private:
	Material mat;
	Vector normal;
};

#endif //__OBJECT_HPP__