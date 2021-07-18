#define __OBJECT_CPP__
#ifdef __OBJECT_CPP__
#include "./Entity.h"
#include "../Materials/Material.h"
#include "../Math/Ray.h"

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

#endif //__ENTITY_CPP__
