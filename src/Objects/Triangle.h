#pragma once

#include "Object.h"

class Triangle : public Object {
public:
    Triangle(const Vector& pos, const Vector& rot, const Vector& scale, const Material& mat, const Point& p1, const Point& p2, const Point& p3);
    Triangle();
    ~Triangle();
    Ray getNormals(const Point& p, const Point& o)const;
    bool intersect(const Ray& ray, Point& impact)const;
    virtual Point getTextureCoordinates(const Point& p) const;

private:
    Point* _points;
};