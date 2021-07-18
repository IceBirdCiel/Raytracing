#include "Plan.h"

Plan::Plan(Vector pos, Vector rot, Material mat) {
	translate(pos[0], pos[1], pos[2]);
	rotateX(rot[0]);
	rotateY(rot[1]);
	rotateZ(rot[2]);
	this->mat = mat;
}

Plan::Plan() {
	translate(0, 0, 0);
	rotateX(0);
	rotateY(0);
	rotateZ(0);
}

Material Plan::getMaterial(const Point& p)const {
	return this->mat;
}

Ray Plan::getNormals(const Point& p, const Point& o)const {
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

bool Plan::intersect(const Ray& ray, Point& impact)const {
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