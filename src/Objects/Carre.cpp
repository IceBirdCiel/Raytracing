#include "Carre.h"

Carre::Carre(Vector pos, Vector rot, float size, float width, float height, Material mat) {
	translate(pos[0], pos[1], pos[2]);
	rotateX(rot[0]);
	rotateY(rot[1]);
	rotateZ(rot[2]);
	scale(size);

	this->width = width;
	this->height = height;
	this->mat = mat;
}

Carre::Carre() {
	this->width = 0;
	this->height = 0;
}

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