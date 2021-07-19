#include "Sphere.h"

Sphere::Sphere(Vector pos, Vector rot, float scale, Material mat): Object(pos,rot,scale,mat) {
	this->mat = mat;
}

Sphere::Sphere(): Object(Vector(0,0,0),Vector(0,0,0),1,Material()){}

Material Sphere::getMaterial(const Point& p)const {
	return this->mat;
}

Ray Sphere::getNormals(const Point& p, const Point& o)const {
	Point obs = globalToLocal(o);
	Point imp = globalToLocal(p);

	Ray ray;
	float distance = 
		sqrt(obs[0] * obs[0] + obs[1] * obs[1] + obs[2] * obs[2]);

	ray.origin = p;

	if (distance < 1) ray.vector = imp * -1;
	else ray.vector = imp;

	ray.vector = ray.vector.normalized();

	return ray;
}

bool Sphere::intersect(const Ray & ray, Point& impact)const {
	Ray r = globalToLocal(ray);

	float a = r.vector[0] * r.vector[0] + r.vector[1] * r.vector[1] + r.vector[2] * r.vector[2];
	float b = 2 * (r.origin[0] * r.vector[0] + r.origin[1] * r.vector[1] + r.origin[2] * r.vector[2]);
	float c = r.origin[0] * r.origin[0] + r.origin[1] * r.origin[1] + r.origin[2] * r.origin[2] - 1;

	float delta = (b * b) - (4 * a * c);

	if (delta < 0) return false;
	else if (delta == 0) {
		float t = -b / (2 * a);
		if (t > 0) {
			float px = r.origin[0] + r.vector[0] * t;
			float py = r.origin[1] + r.vector[1] * t;
			float pz = r.origin[2] + r.vector[2] * t;
			impact[0] = px;
			impact[1] = py;
			impact[2] = pz;
			return true;
		}
		else return false;
	}

	else{
        float t1 = (-b - sqrt(delta))/(2*a);
        float t2 = (-b + sqrt(delta))/(2*a);
        float res;
        if(t1 < 0){
            res = t2;
        }
        if(t2 < 0){
            res = t1;
        }
        if(t1 > 0 && t2 > 0)
        {
            res = (t1 < t2)? t1:t2;
        }
        if(res > 0){
            float px = r.origin[0] + r.vector[0]*res;
            float py = r.origin[1] + r.vector[1]*res;
            float pz = r.origin[2] + r.vector[2]*res;
            impact[0] = px;
            impact[1] = py;
            impact[2] = pz;
            impact = localToGlobal(impact);
            return true;
        }  		 		   		  	 		 
        else{
			return false;
		}
	}
}