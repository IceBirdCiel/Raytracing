#pragma once
#include "./Entity.h"
#include "../Materials/Material.h"
#include "../Math/Ray.h"

class Object : public Entity
{
public:

    Object(){}
    Object(Material mat):m_mat(mat){}
    Object(Vector pos, Vector rot, float scale, Material mat):Entity(pos,rot,Vector(scale,scale,scale)), m_mat(mat){}

    virtual Material getMaterial(const Point& p)const {
        Color white(1,1,1);
        return Material(white,white,white,1);
    };
    virtual Ray getNormal(const Point& p)const {
        return Ray(Point(0,0,0), Vector(1,1,1));
    };
    virtual bool intersect(const Ray& ray, Point& impact)const {return false;};

private:
    Material m_mat{};
};
