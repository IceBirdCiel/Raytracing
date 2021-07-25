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

//moller-trumbore algorithm
bool Triangle::intersect(const Ray &ray, Point &impact) const {
    const float EPSILON = 0.0000001;
    Vector edge1, edge2, s, q;
    Point p0, p1, p2;

    p0 = localToGlobal(_points[0]);
    p1 = localToGlobal(_points[1]);
    p2 = localToGlobal(_points[2]);
    edge1 = p1 - p0;
    edge2 = p2 - p0;
    Vector h = ray.vector.cross(edge2);
    float a = edge1.dot(h);
    if(a > -EPSILON && a < EPSILON) {
        return false;   // ray parallel to triangle
    }

    float f = 1.0f / a;
    s = ray.origin - p0;
    float u = f * s.dot(h);
    if(u < 0.0 || u > 1.0) {
        return false;
    }
    q = s.cross(edge1);
    float v = f * ray.vector.dot(q);
    if(v < 0.0 || u + v > 1.0){
        return false;
    }

    // compute t to know if point intersects on line or not
    float t = f * edge2.dot(q);
    if(t > EPSILON){
        impact = ray.origin + ray.vector * t;
        return true;
    }
    else {
        return false;
    }
}

Point Triangle::getTextureCoordinates(const Point &p) const {
    Point local = globalToLocal(p);
    Vector edge(2,2,2);
    return Point(local[0] / edge[0] + 0.5f, local[1] / edge[1] + 0.5f, 0.0f);
}
