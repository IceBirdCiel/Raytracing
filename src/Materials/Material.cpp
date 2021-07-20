#include "Material.h"

Material::Material(Color a, Color d, Color s, float sh):
        ambient(a),
        diffuse(d),
        specular(s),
        shininess(sh){}

Material::Material() {
    this->ambient = Color(0, 0, 0);
    this->diffuse = Color(0, 0, 0);
    this->specular = Color(0, 0, 0);
    this->shininess = 0;
}