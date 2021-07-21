//
// Created by Antoine on 21/07/2021.
//

#include "SpotLight.h"

SpotLight::SpotLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s) : Light(pos, rot, scale, a, d, s) {

}
Color SpotLight::getIllumination(const Ray& normal, Vector cameraForward, const Material& material) const {
    float lightConstant = 0.5f;
    float lightLinear = 0.5f;
    float lightQuadratic = 0.1f;

    //POINT LIGHT LIGHTING
    //NEEDS TO END UP INSIDE OF RAYTRACER CLASS OR AT LEAST IN A FUNCTION

    Vector impactPos(normal.origin[0],normal.origin[1],normal.origin[2]);
    Vector lightDir = (getPosition() - impactPos).normalized();
    // _diffuse shading
    float diff = std::max(normal.vector.dot(lightDir), 0.0f);
    // _specular shading

    Vector reflectDir = -lightDir - normal.vector * (2 * lightDir.dot(normal.vector));

    float spec = pow(std::max(cameraForward.dot(reflectDir), 0.0f), material.shininess);
    // attenuation
    float distance    = (getPosition() - impactPos).norm();
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
    // combine results
    Color ambient  = _ambient * material.diffuse; //vec3(texture(material._diffuse, TexCoords));
    Color diffuse  = _diffuse * material.diffuse;//l._diffuse  * diff * vec3(texture(material._diffuse, TexCoords));
    //Todo: add the _specular coeff
    Color specular = _specular * material.specular;//l._specular * spec * vec3(texture(material._specular, TexCoords));
    ambient  = ambient * attenuation;
    diffuse  = diffuse * attenuation;
    specular  = specular * attenuation;
    return Color(ambient + diffuse + specular);
}
