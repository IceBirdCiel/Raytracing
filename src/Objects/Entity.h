#pragma once
#include "../Math/Vector.h"
#include "../Math/Point.h"
#include "../Math/Ray.h"
#include "../Math/Matrix.h"

class Entity
{
public:
    Entity(const Vector&  pos, const Vector&  rot, const Vector&  scale);
    Entity();
    virtual ~Entity() = default;

    void translate(float x, float y, float z);
    void rotateX(float deg);
    void rotateY(float deg);
    void rotateZ(float deg);
    void scale(Vector s);

    Point localToGlobal(const Point& p)const;
    Point globalToLocal(const Point& p)const;

    Vector localToGlobal(const Vector& v)const;
    Vector globalToLocal(const Vector& v)const;

    Ray localToGlobal(const Ray& r)const;
    Ray globalToLocal(const Ray& r)const;
    Vector right() const;
    Vector up() const;
    Vector forward() const;

    Point getPosition() const;

    void printTransform() const;

private:
    Matrix trans;
    Matrix transInv;
    Vector _position;
    static double degToRad;
    void addToTransform(const Vector& pos, const Vector& rot, const Vector& scale);
};