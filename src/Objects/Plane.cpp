#include "Plane.h"

Plane::Plane(Vector pos, Vector rot, Material mat):Object(pos,rot,Vector(1,1,1),mat) {}

Plane::Plane():Object() {}

Ray Plane::getNormals(const Point& p, const Point& o)const {
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

bool Plane::intersect(const Ray& ray, Point& impact)const {
	Ray r = globalToLocal(ray);
	float oz = r.origin[2];
	float vz = r.vector[2];

	float t = -1 * (oz / vz);

	if (t > 0) {
		float px = r.origin[0] + r.vector[0] * t;
		float py = r.origin[1] + r.vector[1] * t;
		float pz = r.origin[2] + r.vector[2] * t;

		impact[0] = px;
		impact[1] = py;
		impact[2] = pz;
		impact = localToGlobal(impact);
		return true;
	}
	else return false;
}