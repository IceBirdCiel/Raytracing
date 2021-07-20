#pragma once

#include <vector>
#include "../Materials/Color.h"
#include "../Objects/Light.h"
#include "../Objects/Sphere.h"

class Scene
{
public:
    Scene(){};
    Color getBackground() const;
    Color getAmbiant() const;

    void setAmbiant(Color color);
    void setBackground(Color color);

    int nbLights() const;
    [[nodiscard]] const Light getLight(int index) const;
    void addLight(Light light);
    void addObject(Sphere object);
    bool closestObjectIntersected(Ray ray, Sphere& object, Point& closestImpact) const ;
private:
    std::vector<Light> _lights;
    std::vector<Sphere> _objects;
    Color _background;
    Color _ambiant;
};

