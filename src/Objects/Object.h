#pragma once
#include "./Entity.h"
#include "../Materials/Material.h"
#include "../Math/Ray.h"

class Object : public Entity
{
public:

    Object(){}
    //Object(Material mat):m_mat(mat){}
    Object(const Vector&  pos, const Vector&  rot, const Vector& scale, const Material& mat):Entity(pos,rot,scale), m_mat(mat), m_mat2(mat), m_duo(false) {}
    Object(const Vector&  pos, const Vector&  rot, const Vector& scale, const Material& mat, const Material& mat2, int repeat):Entity(pos,rot,scale), m_mat(mat), m_mat2(mat2), m_repeat(repeat), m_duo(true) {}

    [[nodiscard]] virtual Material getMaterial(const Point& p) const {
        return m_mat;
    }

    [[nodiscard]] virtual Ray getNormals(const Point& p, const Point& o)const = 0;
    virtual bool intersect(const Ray& ray, Point& impact)const = 0;

    [[nodiscard]] virtual Point getTextureCoordinates(const Point& p) const = 0;

private:
    bool dualMaterials;
protected:
    Material m_mat{};
    Material m_mat2{};
    int m_repeat;
    bool m_duo;
};
