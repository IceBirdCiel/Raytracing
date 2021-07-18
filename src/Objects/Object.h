#define __OBJECT_CPP__
#ifdef __OBJECT_CPP__
#include "./Entity.h"
#include "../Materials/Material.h"
#include "../Math/Ray.h"

class Object : public Entity
{
public:
    virtual Material getMaterial(const Point& p)const;
    virtual Ray getNormal(const Point& p)const;
    virtual bool intersect(const Ray& ray, Point& impact)const;

private:
    Material mat;
};

#endif //__ENTITY_CPP__
