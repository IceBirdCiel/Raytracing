#include "Light.h"

Light::Light(Vector pos, Vector rot, Vector s):position(pos),
	rotation(rot),
	size(s){}

//Check if those formula are ok, 
//else correct then with matrix trans and transInv
Ray Light::getRayToLight(const Point& p)const {
	Vector vec(this->position - Vector(p[0], p[1], p[2]));
	return Ray(p,vec.normalized());
}

Ray Light::getRayFromLight(const Point& p)const {
	Vector vec(Vector(p[0], p[1], p[2]) - this->position);
	return Ray(Point(position[0], position[1], position[2]), 
		vec.normalized());
}

Vector Light::getVectorToLight(const Point& p)const {
	Vector vec(this->position - Vector(p[0], p[1], p[2]));
	return vec.normalized();
}

Vector Light::getVectorFromLight(const Point& p)const {
	Vector vec(Vector(p[0], p[1], p[2]) - this->position);
	return vec.normalized();
}