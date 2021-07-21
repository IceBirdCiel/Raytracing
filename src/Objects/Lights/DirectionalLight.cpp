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

    Vector reflect = dir + normal.vector * 2 * dir.dot(normal.vector);
    float angle1 = pow(normal.vector.dot(reflect), material.shininess);
    angle1 = (angle1 < 0) ? 0 : angle1;
    specular = material.specular * _specular * angle1;

    Color phong = lambert + specular;

    return phong;
}