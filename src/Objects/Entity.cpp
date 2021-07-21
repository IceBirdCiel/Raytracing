#include "Entity.h"

Entity::Entity(Vector pos, Vector rot,Vector s) {
    scale(s);
    rotateX(rot[0]);
    rotateY(rot[1]);
    rotateZ(rot[2]);
    translate(pos[0], pos[1], pos[2]);
}

Entity::Entity() {}


void Entity::translate(float x, float y, float z) {
    Matrix m;
    m(0, 3) = x;
    m(1, 3) = y;
    m(2, 3) = z;

    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateX(float deg) {
    Matrix m;
    m(1, 1) = cos(deg);
    m(1, 2) = -sin(deg);
    m(2, 1) = sin(deg);
    m(2, 2) = cos(deg);

    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateY(float deg) {
    Matrix m;
    m(0, 0) = cos(deg);
    m(0, 2) = sin(deg);
    m(2, 0) = -sin(deg);
    m(2, 2) = cos(deg);

    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateZ(float deg) {
    Matrix m;
    m(0, 0) = cos(deg);
    m(0, 1) = -sin(deg);
    m(1, 0) = sin(deg);
    m(1, 1) = cos(deg);


    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::scale(Vector s) {
    Matrix m;
    m(0, 0) = s[0];
    m(1, 1) = s[1];
    m(2, 2) = s[2];

    trans = m * trans;
    transInv = trans.inverse();
}

Point Entity::localToGlobal(const Point& p) const{
    Point res = trans * p;
    return res;
}

Point Entity::globalToLocal(const Point& p)const {
    Point res = transInv * p;
    return res;
}

Vector Entity::localToGlobal(const Vector& v)const {
    Vector vec = trans * v;
    return vec;
}

Vector Entity::globalToLocal(const Vector& v)const {
    Vector res = transInv * v;
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

void Entity::printTransform() const {
    std::cout << trans <<std::endl;
}

Vector Entity::getPosition() const {
    return localToGlobal(Vector(0,0,0));
}

Vector Entity::right() const {
    return localToGlobal(Vector(1,0,0));
}
Vector Entity::up() const {
    return localToGlobal(Vector(0,1,0));
}
Vector Entity::forward() const {
    return localToGlobal(Vector(0,0,1));
}
