#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s, float i) :
	Light(pos, rot, scale, a, d, s, i){}

float DirectionalLight::getLightingBehaviour(Ray normal, Vector& direction) const {
    direction = this->forward().normalized();
    return 1;
}