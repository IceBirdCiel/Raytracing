#define _USE_MATH_DEFINES
#include <cmath>
#include "Sphere.h"

Sphere::Sphere(const Vector&  pos, const Vector&  rot, const Vector& scale, const Material& mat): Object(pos,rot,scale,mat) {}
Sphere::Sphere(const Vector&  pos, const Vector&  rot, const Vector& scale, const Material& mat, const Material& mat2, int repeat): Object(pos,rot,scale,mat,mat2,repeat) {}

Sphere::Sphere(): Object(){}

Ray Sphere::getNormals(const Point& impact, const Point& observer) const {
	Point obs = globalToLocal(observer);
	Point imp = globalToLocal(impact);
	Vector v = sqrt(pow(obs[0], 2) + pow(obs[1], 2) + pow(obs[2], 2)) < 1 ? Vector(-imp[0], -imp[1], -imp[2]) : Vector(imp[0], imp[1], imp[2]);
	Ray r(imp, v.normalized());
	r = localToGlobal(r);
    r.vector = r.vector.normalized();
	return r;
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
        float res = 0;
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

Point Sphere::getTextureCoordinates(const Point &p) const {
    Point lp = globalToLocal(p);
    float rho = std::sqrt(lp.dot(lp));
    float theta = std::atan2(lp[1], lp[0]);
    float sigma = std::acos(lp[2]/rho);
    float x = -theta/(2*M_PI)+0.5f;
    float y = sigma/M_PI;
    return Point(x, y, 0);
}
Material Sphere::getMaterial(const Point& p) const {
    //return m_mat;
    if(!m_duo)return m_mat;
    //std::cout << "IBIDIBABIDIBOU ! m_duo " << m_duo << "\n";
    Point coordinates = getTextureCoordinates(p);
    float x = fmod(coordinates[0]*2*m_repeat, 2);
    float y = fmod(coordinates[1]*m_repeat, 2);
    if(y < 1.f){
        x = 2-x;
    }
    if( x < 1.f){
        return m_mat;
    }else{
        return m_mat2;
    }
}