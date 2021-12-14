#include "Light.h"


Light::Light(Vector pos, Vector rot, float scale, Color a, Color d, Color s, float i): Entity(pos,rot,Vector(scale,scale,scale)), _ambient(a), _diffuse(d), _specular(s), intensity(i) {

}

Color Light::Ambient() const {
    return _ambient;
}
Color Light::Specular() const {
    return _specular;
}
Color Light::Diffuse() const {
    return _diffuse;
}