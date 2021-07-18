#include "Entity.h"

Entity::Entity(Vector pos, Vector rot, Vector s):
        position(pos),
        rotation(rot),
        size(s){}

Entity::Entity() : position(0, 0, 0),
                   rotation(0, 0, 0),
                   size(1, 1, 1) {}

void Entity::translate(float x, float y, float z) {
    Matrix m;
    m(0, 3) = x;
    m(1, 3) = y;
    m(2, 3) = z;

    position = m * position;
    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateX(float deg) {
    Matrix m;
    m(1, 1) = cos(deg);
    m(1, 2) = -sin(deg);
    m(2, 1) = sin(deg);
    m(2, 2) = cos(deg);

    rotation = m * rotation;
    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateY(float deg) {
    Matrix m;
    m(0, 0) = cos(deg);
    m(0, 2) = sin(deg);
    m(2, 0) = -sin(deg);
    m(2, 2) = cos(deg);

    rotation = m * rotation;
    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateZ(float deg) {
    Matrix m;
    m(0, 0) = cos(deg);
    m(0, 1) = -sin(deg);
    m(1, 0) = sin(deg);
    m(1, 1) = cos(deg);

    rotation = m * rotation;

    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::scale(float factor) {
    Matrix m;
    m(0, 0) = factor;
    m(1, 1) = factor;
    m(2, 2) = factor;

    size = m * size;
    trans = m * trans;
    transInv = trans.inverse();
}

Point Entity::localToGlobal(const Point& p) const{
    Point res = transInv * p;
    return res;
}

Point Entity::globalToLocal(const Point& p)const {
    Point res = trans * p;
    return res;
}

Vector Entity::localToGlobal(const Vector& v)const {
    Vector vec = transInv * v;
    return vec;
}

Vector Entity::globalToLocal(const Vector& v)const {
    Vector res = trans * v;
    return res;
}

Ray Entity::localToGlobal(const Ray& r)const {
    Point origin = localToGlobal(r.origin);
    Vector vector = localToGlobal(r.vector);
    return Ray(origin, vector);
}

Ray Entity::globalToLocal(const Ray& r)const {
    Point origin = globalToLocal(r.origin);
    Vector vector = globalToLocal(r.vector);
    return Ray(origin, vector);
}