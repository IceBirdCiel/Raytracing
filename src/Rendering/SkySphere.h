#pragma once

#include <string>
#include "Image.h"
#include "../Math/Ray.h"
#include "../Objects/Sphere.h"
#include "../Objects/Camera.h"

class SkySphere : public Sphere {
public:
    SkySphere(float scale, Material material, const Camera& camera);
};

