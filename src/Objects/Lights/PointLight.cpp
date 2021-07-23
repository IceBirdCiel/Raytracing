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
/*
Color PointLight::getLambert(const Ray& normal, Vector cameraForward, const Material& material, const Object& obj)const {
    float lightConstant = 0.5f;
    float lightLinear = 0.5f;
    float lightQuadratic = 0.1f;

    Point dirpoint = (getPosition() - normal.origin);
    Vector lightDir = Vector(dirpoint[0], dirpoint[1], dirpoint[2]);
    float distance = lightDir.norm();
    lightDir = lightDir.normalized();
    // _diffuse shading
    float diff = std::max(normal.vector.dot(lightDir), 0.0f);

    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
    // combine results
    Color ambient = _ambient * material.diffuse;
    Color diffuse = _diffuse * material.diffuse;

    if (material.texture != nullptr) {
        Point texCoords = obj.getTextureCoordinates(normal.origin);
        int x = texCoords[0] * (material.texture->getWidth() - 1);
        int y = texCoords[1] * (material.texture->getHeight() - 1);
        Color pixelColor = material.texture->getColor(x, y);
        //std::cout << pixelColor.r << ", " << pixelColor.g << ", "  << pixelColor.b << std::endl;
        diffuse = pixelColor * diffuse;
    }

    ambient = ambient * attenuation;
    diffuse = diffuse * attenuation;

    return Color(ambient + diffuse);
}

Color PointLight::getPhong(const Ray& normal, Vector cameraForward, const Material& material, const Object& obj) const {
    float lightConstant = 0.5f;
    float lightLinear = 0.5f;
    float lightQuadratic = 0.1f;

    Color lambert = getLambert(normal, cameraForward, material, obj);

    Point dirpoint = (getPosition() - normal.origin);
    Vector lightDir = Vector(dirpoint[0], dirpoint[1], dirpoint[2]);
    float distance    = lightDir.norm();
    lightDir = lightDir.normalized();

    Vector reflectDir = -lightDir - normal.vector * (2 * lightDir.dot(normal.vector));

    float spec = pow(std::max(cameraForward.dot(reflectDir), 0.0f), material.shininess);

    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

    Color specular = _specular * material.specular;//l._specular * spec * vec3(texture(material._specular, TexCoords));

    specular  = specular * attenuation;
    return Color(lambert + specular);
}
*/
