#include "Carre.h"

Carre::Carre(const Vector& pos,const  Vector& rot, float scale,const  Material& mat) : Object(pos,rot,scale,mat){
	this->mat = mat;
}

Carre::Carre(): Object(Vector(0, 0, 0), Vector(0, 0, 0), 1, Material()) {}

Material Carre::getMaterial(const Point& p)const {
	return this->mat;
}

Ray Carre::getNormals(const Point& p, const Point& o)const {
	Point point = globalToLocal(o);
	Point imp = globalToLocal(p);
	Ray ray;

	ray.origin = imp;
	ray.vector[0] = 0;
	ray.vector[1] = 0;

	if (point[2] < 0) ray.vector[2] = -1;
	else ray.vector[2] = 1;

	ray = localToGlobal(ray);

	return ray;
}

bool Carre::intersect(const Ray& ray, Point& impact)const {
	Ray r = globalToLocal(ray);
	float oz = r.origin[2];
	float vz = r.vector[2];

	float t = -1 * (oz / vz);
	float px = r.origin[0] + r.vector[0] * t;
	float py = r.origin[1] + r.vector[1] * t;
	float pz = r.origin[2] + r.vector[2] * t;

	if (t > 0 && px < 1 && px >= -1 && py < 1 && py >= -1) {
		impact[0] = px;
		impact[0] = py;
		impact[0] = pz;
		impact = localToGlobal(impact);
		return true;
	}
	else false;
}