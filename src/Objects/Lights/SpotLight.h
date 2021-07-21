#pragma once
#include "Light.h"

class SpotLight: public Light {
public:
    SpotLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s);
    [[nodiscard]] Color getIllumination(const Ray& normal,Vector cameraForward, const Material& material) const override;
};