#pragma once

#include <string>
#include "Image.h"
#include "../Math/Ray.h"
#include "../Objects/Sphere.h"

class SkySphere : Sphere {
public:
    SkySphere(const std::string& image);
    Color getColor(Ray ray);
    virtual Point getTextureCoordinates(const Point& p) const;

private:
    // todo to move to material
    Image m_image;
};

