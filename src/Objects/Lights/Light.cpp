#include "Light.h"


Light::Light(Vector pos, Vector rot, float scale, Color a, Color d, Color s): Entity(pos,rot,Vector(scale,scale,scale)), _ambient(a), _diffuse(d), _specular(s) {

}
/*

//Check if those formula are ok, 
//else correct then with matrix trans and transInv
Ray Light::getRayToLight(const Point& p)const {
    Vector vec(getPosition() - Vector(p[0], p[1], p[2]));
    return Ray(p,vec.normalized());
}

Ray Light::getRayFromLight(const Point& p)const {
    Point pos = getPosition();
    Vector vec(Vector(p[0], p[1], p[2]) - pos);
    return Ray(Point(pos[0], pos[1], pos[2]),
               vec.normalized());
}

Vector Light::getVectorToLight(const Point& p)const {
    Vector vec(getPosition() - Vector(p[0], p[1], p[2]));
    return vec.normalized();
}

Vector Light::getVectorFromLight(const Point& p)const {
    Vector vec(Vector(p[0], p[1], p[2]) - getPosition());
    return vec.normalized();
}*/