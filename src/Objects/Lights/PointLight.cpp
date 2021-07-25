//
// Created by Antoine on 21/07/2021.
//

#include "PointLight.h"

PointLight::PointLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s,float lightC, float lightL, float lightQ, float i) : Light(pos, rot, scale, a, d, s, i), lightConstant(lightC), lightLinear(lightL), lightQuadratic(lightQ) {

}

float PointLight::getLightingBehaviour(Ray normal, Vector& direction) const {
    Point dirpoint = (getPosition() - normal.origin);
    direction = Vector(dirpoint[0], dirpoint[1], dirpoint[2]);
    float distance = direction.norm();
    direction = direction.normalized();
    return 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
}
