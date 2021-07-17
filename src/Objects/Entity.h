#define __ENTITY_CPP__
#ifdef __ENTITY_CPP__
#include "../Math/Vector.h"
#include "../Math/Point.h"
#include "../Math/Ray.h"
#include "../Math/Matrix.h"

class Entity
{
public:
    Entity(Vector pos, Vector rot, Vector s);
    Entity();

    void translate(float x, float y, float z);
    void rotateX(float deg);
    void rotateY(float deg);
    void rotateZ(float deg);
    void scale(float factor);

    Point localToGlobal(const Point& p)const;
    Point globalToLocal(const Point& p)const;

    Vector localToGlobal(const Vector& v)const;
    Vector globalToLocal(const Vector& v)const;

    Ray localToGlobal(const Ray& r)const;
    Ray globalToLocal(const Ray& r)const;

private:
    Vector position;
    Vector rotation;
    Vector size;
    Matrix trans;
    Matrix transInv;

};
#endif //__ENTITY_CPP__
