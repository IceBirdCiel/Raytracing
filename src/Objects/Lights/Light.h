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
    virtual float getLightingBehaviour(Ray normal, Vector& direction) const = 0;
    float intensity;
    virtual Color Ambient() const;
    virtual Color Diffuse() const;
    virtual Color Specular() const;
private:
    Color _ambient;
    Color _diffuse;
    Color _specular;
};



