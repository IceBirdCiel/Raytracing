#include "Cone.h"

Cone::Cone(const Vector& pos, const Vector& rot, const Vector& scale, Material mat) : Object(pos,rot,scale,mat) {}

Cone::Cone(): Object(){}

Ray Cone::getNormals(const Point& p, const Point& o)const {
    Point imp = globalToLocal(p);

    Ray ray;
    ray.origin = imp;
    ray.vector[0] = imp[0];
    ray.vector[1] = 0;
    ray.vector[2] = imp[2];

    ray = localToGlobal(ray);
    ray.vector = ray.vector.normalized();
    return ray;
}

bool Cone::intersect(const Ray& ray, Point& impact)const {
    Ray r = globalToLocal(ray);

    float a = r.vector[0] * r.vector[0] + r.vector[2] * r.vector[2] - r.vector[1] * r.vector[1];
    float b = 2 * (r.origin[0] * r.vector[0] - r.origin[2] * r.vector[2] + r.vector[1] * r.origin[1]);
    float c = r.origin[0] * r.origin[0] + r.origin[1] * r.origin[1] - (r.origin[2]-1) * (r.origin[2]-1);

    float delta = (b * b) - (4 * a * c);
    if (delta < 0)
    {
        return false;
    }

    else {
        float t1 = (-b - sqrt(delta)) / (2 * a);
        float t2 = (-b + sqrt(delta)) / (2 * a);
        float res = 0;
        if (t1 < 0) {
            res = t2;
        }
        if (t2 < 0) {
            res = t1;
        }
        if (t1 > 0.001 && t2 > 0.001)
        {
            res = (t1 < t2) ? t1 : t2;
        }
        if (res > 0.001) {

            float check = r.origin[0] + res * r.vector[1];

            if (check < r.origin[1]) {
                float px = r.origin[0] + res * r.vector[0];
                float py = r.origin[1] + res * r.vector[1];
                float pz = r.origin[2] + res * r.vector[2];
                impact[0] = px;
                impact[1] = py;
                impact[2] = pz;
                impact = localToGlobal(impact);
                return true;
            }
        }
        return false;
    }
}


Point Cone::getTextureCoordinates(const Point& p) const {
	return Point();
}