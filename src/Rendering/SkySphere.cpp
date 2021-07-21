#include "SkySphere.h"

SkySphere::SkySphere(const std::string &image) : m_image(image){
}

Color SkySphere::getColor(Ray ray) {
    /*float x = (atan(ray.vector[2] / ray.vector[0]) / 6.283185307179586476925286766559f) + 0.5f;
    float y = (acos(ray.vector[1]) / 3.1415926535897932384626433832795f);
    return m_image.getColor(x * m_image.getWidth(),y * m_image.getHeight());*/
    return Color(0,0,0);
}

Point SkySphere::getTextureCoordinates(const Point &p) const {
    //todo
    return Sphere::getTextureCoordinates(p);
}
