#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s);

	Color getLambert(const Ray& normal, Vector cameraForward, const Material& material) const override;
	Color getPhong(const Ray& normal, Vector cameraForward, const Material& material) const override;
};