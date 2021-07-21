#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector pos, Vector rot, float scale, Color a, Color d, Color s) :
	Light(pos, rot, scale, a, d, s){}

Color DirectionalLight::getLambert(const Ray& normal, Vector cameraForward, const Material& material) const {
    //return Color(normal.vector[0], normal.vector[1], normal.vector[2]);
    Color ambiant = material.ambient * _ambient;
    Vector dir = this->forward();
    
    Color diffuse(0,0,0);
    float angle = normal.vector.dot(dir);
    diffuse = material.diffuse * _diffuse * angle;

    Color lambert = ambiant + diffuse;

    return lambert;
}

Color DirectionalLight::getPhong(const Ray& normal, Vector cameraForward, const Material& material) const {
    Vector dir = this->forward();
    Color lambert = getLambert(normal, cameraForward, material);
    
    Color specular(0,0,0);

    //Vector reflect = dir - normal.vector * ( 2 * dir.dot(normal.vector));
    Vector reflect = normal.vector.normalized().reflect(dir);
    //float spec = pow(material.shininess, cameraForward.dot(reflect));
    float spec = pow(std::max(cameraForward.dot(reflect), 0.f), material.shininess);
    //spec = (spec < 0) ? 0 : spec;
    specular = material.specular * _specular * spec;
    Color phong = lambert + specular;

    return phong;
}