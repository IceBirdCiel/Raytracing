#include "Light.h"


Light::Light(Vector pos, Vector rot, float scale, Color a, Color d, Color s): Entity(pos,rot,Vector(scale,scale,scale)), _ambient(a), _diffuse(d), _specular(s) {

}

Color Light::getLambert(const Ray& normal, Vector cameraForward, const Material& material, const Object& obj) const {
    //return Color(normal.vector[0], normal.vector[1], normal.vector[2]);

    Vector dir;

    float attenuation = getLightingBehaviour(normal,dir);

    Color ambiant = material.ambient * _ambient * attenuation;
    Color diffuse = material.diffuse;
    float angle = normal.vector.dot(dir);

    if(material.texture != nullptr){
        Point texCoords = obj.getTextureCoordinates(normal.origin);
        int x = texCoords[0] * (material.texture->getWidth() - 1);
        int y = texCoords[1] * (material.texture->getHeight() - 1);
        Color pixelColor = material.texture->getColor(x, y);
        //std::cout << pixelColor.r << ", " << pixelColor.g << ", "  << pixelColor.b << std::endl;
        diffuse = pixelColor * diffuse;
    }

    diffuse = diffuse * _diffuse * angle * attenuation;

    Color lambert = ambiant + diffuse;

    return lambert;
}

Color Light::getPhong(const Ray& normal, Vector cameraForward, const Material& material, const Object& obj) const {
    Vector dir;

    float attenuation = getLightingBehaviour(normal,dir);

    Color lambert = getLambert(normal, cameraForward, material, obj);

    //Vector reflect = dir - normal.vector * ( 2 * dir.dot(normal.vector));
    Vector reflect = normal.vector.normalized().reflect(dir);
    //float spec = pow(material.shininess, cameraForward.dot(reflect));
    float spec = pow(std::max(cameraForward.dot(reflect), 0.f), material.shininess);
    //spec = (spec < 0) ? 0 : spec;
    Color specular = material.specular * _specular * spec * attenuation;
    Color phong = lambert + specular;

    return phong;
}
/*

//Check if those formula are ok, 
//else correct then with matrix trans and transInv
Ray Light::getRayToLight(const Point& p)const {
    Vector vec(getPosition() - Vector(p[0], p[1], p[2]));
    return Ray(p,vec.normalized());
}

Ray Light::getRayFromLight(const Point& p)const {
    Point pos = getPosition();
    Vector vec(Vector(p[0], p[1], p[2]) - pos);
    return Ray(Point(pos[0], pos[1], pos[2]),
               vec.normalized());
}

Vector Light::getVectorToLight(const Point& p)const {
    Vector vec(getPosition() - Vector(p[0], p[1], p[2]));
    return vec.normalized();
}

Vector Light::getVectorFromLight(const Point& p)const {
    Vector vec(Vector(p[0], p[1], p[2]) - getPosition());
    return vec.normalized();
}*/