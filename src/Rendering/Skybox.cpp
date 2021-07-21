#include "Skybox.h"

Skybox::Skybox(const std::string &image) : m_image(image){
}

Color Skybox::getColor(Ray ray) {
    float x = (atan(ray.vector[2] / ray.vector[0]) / 6.283185307179586476925286766559f)+ 0.5f;
    float y = (acos(ray.vector[1]) / 3.1415926535897932384626433832795f);
    //std::cout << x << " ; " << y << std::endl;
    return m_image.getColor(x,y);
}
