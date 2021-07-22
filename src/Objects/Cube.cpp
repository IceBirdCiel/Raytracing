#include "Cube.h"

Cube::Cube(const Vector& pos,const  Vector& rot, const Vector& size,const  Material& mat) : Object(pos,rot,size, mat) {}

Cube::Cube() {}


Ray Cube::getNormals(const Point& p, const Point& o)const {
    Vector n(0, 0, 0);
    Point imp = globalToLocal(p);
    Point obs = globalToLocal(o);

    if (abs(imp[0] - 1) < 0.0001) n[0] = 1;
    if (abs(imp[0] + 1) < 0.0001) n[0] = -1;
    if (abs(imp[1] - 1) < 0.0001) n[1] = 1;
    if (abs(imp[1] + 1) < 0.0001) n[1] = -1;
    if (abs(imp[2] - 1) < 0.0001) n[2] = 1;
    if (abs(imp[2] + 1) < 0.0001) n[2] = -1;

    if (obs[0]< 1 && obs[0]> -1 && obs[1]< 1 && obs[1]> -1 && obs[2]< 1 && obs[2]> -1) {
        n = -n;
    }

    n = localToGlobal(n);
    n = n.normalized();
    Ray r(p, n);

    return r;
}

bool Cube::intersect(const Ray& ray, Point& impact)const {
    Ray r = globalToLocal(ray);

    float x = 1 / r.vector[0];
    float y = 1 / r.vector[1];
    float z = 1 / r.vector[2];

    float t1 = (-1 - r.origin[0]) * x;
    float t2 = (1 - r.origin[0]) * x;
    float t3 = (-1 - r.origin[1]) * y;
    float t4 = (1 - r.origin[1]) * y;
    float t5 = (-1 - r.origin[2]) * z;
    float t6 = (1 - r.origin[2]) * z;

    float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

    if (tmax < 0) {
        return false;
    }
    if (tmin > tmax) {
        return false;
    }

    float t = tmin;

    impact[0] = r.origin[0] + r.vector[0] * t;
    impact[1] = r.origin[1] + r.vector[1] * t;
    impact[2] = r.origin[2] + r.vector[2] * t;
    impact = localToGlobal(impact);
    return true;
}

float Cube::min(const float a, const float b)const {
    return (a < b) ? a : b;
}

float Cube::max(const float a, const float b)const {
    return (a > b) ? a : b;
}

Point Cube::getTextureCoordinates(const Point &p) const {
    //todo
    return Point();
}
