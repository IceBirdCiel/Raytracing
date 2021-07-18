#define __OBJECT_CPP__
#ifdef __OBJECT_CPP__
#include "./Entity.h"
#include "../Materials/Material.h"
#include "../Math/Ray.h"

class Object : public Entity
{
public:
    virtual Material getMaterial(const Point& p)const {
        Color white(1,1,1);
        return Material(white,white,white,1);
    };
    virtual Ray getNormal(const Point& p)const {
        return Ray(Point(0,0,0), Vector(1,1,1));
    };
    virtual bool intersect(const Ray& ray, Point& impact)const {return false;};

private:
    Material mat;
};


#endif //__ENTITY_CPP__
