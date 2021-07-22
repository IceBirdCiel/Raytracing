#pragma once
#include "Light.h"

class PointLight: public Light {
public:
    PointLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s);
    [[nodiscard]] Color getPhong(const Ray& normal,Vector cameraForward, const Material& material, const Object& obj) const override;
};