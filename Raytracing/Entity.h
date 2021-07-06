#define __ENTITY_CPP__
#ifdef __ENTITY_CPP__
#include "Vector.h"
#include "Point.h"
#include "Ray.h"

class Entity
{
public:
	Entity(Vector pos, Vector rot, Vector s);

	void translate(float x, float y, float z);
	void rotateX(float deg);
	void rotateY(float deg);
	void rotateZ(float deg);
	void scale(float factor);
	
	Point localToGlobal(Point p);
	Point globalToLocal(Point p);

	Vector localToGlobal(const Vector& v)const;
	
	Ray localToGlobal(const Ray& r)const;

private:
	Vector position;
	Vector rotation;
	Vector size;

};
#endif //__ENTITY_CPP__
