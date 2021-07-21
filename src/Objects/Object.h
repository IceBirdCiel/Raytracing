#pragma once
#include "./Entity.h"
#include "../Materials/Material.h"
#include "../Math/Ray.h"

class Object : public Entity
{
public:

    Object(){}
    //Object(Material mat):m_mat(mat){}
    Object(const Vector&  pos, const Vector&  rot, const Vector& scale, const Material& mat):Entity(pos,rot,scale), m_mat(mat){}

    [[nodiscard]] virtual Material getMaterial(const Point& p) const {
        return this->m_mat;
    }

    [[nodiscard]] virtual Ray getNormals(const Point& p, const Point& o)const = 0;
    virtual bool intersect(const Ray& ray, Point& impact)const = 0;

private:
    Material m_mat{};
};
