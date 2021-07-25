#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s, float i);
    float getLightingBehaviour(Ray normal, Vector& direction) const override;
};