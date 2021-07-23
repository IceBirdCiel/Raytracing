#pragma once
#include "Light.h"

class PointLight: public Light {
public:
    PointLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s,float lightC, float lightL, float lightQ);
    float getLightingBehaviour(Ray normal, Vector& direction) const override;
private:
    float lightConstant = 0.5f;
    float lightLinear = 0.5f;
    float lightQuadratic = 0.1f;

    //[[nodiscard]] Color getLambert(const Ray& normal,Vector cameraForward, const Material& material, const Object& obj) const override;
    //[[nodiscard]] Color getPhong(const Ray& normal,Vector cameraForward, const Material& material, const Object& obj) const override;
};