#include "Ray.h"

Ray::Ray(float ox, float oy, float oz, float vx, float vy, float vz) : origin(Point(ox, oy, oz)), vector(Vector(vx,vy,vz))
{
}

Ray::Ray(Point o, Vector v): origin(o), vector(v)
{
}

Ray::Ray() : origin(0, 0, 0), vector(0, 0, 0){}

std::ostream& operator<<(std::ostream &os, const Ray& r) {
    os << "Origin: (" << r.origin[0] << ", " << r.origin[1] << ", " << r.origin[2] << ") ; ";
    os << "Direction: (" << r.vector[0] << ", " << r.vector[1] << ", " << r.vector[2] << ")";
    return os;
}

Ray Ray::normalized() const {
    Vector nVec = vector.normalized();
    return Ray(origin, nVec);
}
