#pragma once
#include "../Entity.h"
#include "../../Materials/Color.h"
#include "../../Math/Ray.h"
#include "../../Math/Point.h"
#include "../../Math/Vector.h"
#include "../../Materials/Material.h"
#include "../Object.h"

class Light: public Entity
{
public:
    Light(Vector pos, Vector rot, float scale, Color a, Color d, Color s, float i);
    virtual Color getLambert(const Ray& normal,Vector cameraForward, const Material& material, const Object& obj) const;
    virtual Color getPhong(const Ray& normal,Vector cameraForward, const Material& material, const Object& obj) const;
    virtual float getLightingBehaviour(Ray normal, Vector& direction) const = 0;
    /*Ray getRayToLight(const Point& p)const;
    Ray getRayFromLight(const Point& p)const;
    Vector getVectorToLight(const Point& p)const;
    Vector getVectorFromLight(const Point& p)const;*/
    float intensity;
    virtual Color Ambient() const;
    virtual Color Diffuse() const;
    virtual Color Specular() const;
private:
    bool castShadow(const Point& impact,const Vector& direction) const;
    Color _ambient;
    Color _diffuse;
    Color _specular;
};



