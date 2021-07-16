#include "Material.h"

Material::Material(Color a, Color d, Color s, float sh):
	ka(a),
	kd(d),
	ks(s),
	shininess(sh){}

Material::Material() {
	this->ka = Color(0, 0, 0);
	this->kd = Color(0, 0, 0);
	this->ks = Color(0, 0, 0);
	this->shininess = 0;
}