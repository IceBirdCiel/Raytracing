#include "Triangle.h"

Triangle::Triangle(const Vector &pos, const Vector &rot, const Vector &scale, const Material &mat, const Point& p1, const Point& p2, const Point& p3) : Object(pos, rot, scale, mat) {
    _points = new Point[3];
    _points[0] = p1;
    _points[1] = p2;
    _points[2] = p3;
}

Triangle::Triangle() : Object() {

}

Triangle::~Triangle() {
    delete [] _points;
}

Ray Triangle::getNormals(const Point &p, const Point &o) const {
    Point point = globalToLocal(o);
    Point imp = globalToLocal(p);
    Ray ray;

    ray.origin = imp;
    ray.vector[0] = 0;
    ray.vector[1] = 0;

    if(point[2] < 0) ray.vector[2] = -1;
    else ray.vector[2] = 1;

    ray.vector = ray.vector.normalized();
    ray = localToGlobal(ray);

    return ray;
}

bool Triangle::intersect(const Ray &ray, Point &impact) const {
    Ray r = globalToLocal(ray);
    float oz = r.origin[2];
    float vz = r.vector[2];

    float t = -1 * (oz / vz);
    float px = r.origin[0] + r.vector[0] * t;
    float py = r.origin[1] + r.vector[1] * t;

    if (t > 0 && px < 1 && px >= -1 && py < 1 && py >= -1) {
        impact[0] = px;
        impact[1] = py;
        impact[2] = 0;
        impact = localToGlobal(impact);
        return true;
    }
    return false;
}

Point Triangle::getTextureCoordinates(const Point &p) const {
    Point local = globalToLocal(p);
    Vector edge(2,2,2);
    return Point(local[0] / edge[0] + 0.5f, local[1] / edge[1] + 0.5f, 0.0f);
}
