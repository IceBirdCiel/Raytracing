#pragma once

#include <vector>
#include "../Materials/Color.h"
#include "../Objects/Lights/Light.h"
#include "../Objects/Sphere.h"
#include "../Rendering/Image.h"
#include "../Rendering/SkySphere.h"

class Scene
{
public:
    Scene(){};
    Color getBackground(const Ray& ray) const;
    Color getAmbiant() const;

    void setAmbiant(Color color);
    void setBackground(Color color);
    void setSkybox(SkySphere* skybox);

    int nbLights() const;
    [[nodiscard]] Light* getLight(int index) const;
    void addLight(Light* light);
    void addObject(Object* object);
    Object* closestObjectIntersected(Ray ray, Point& closestImpact) const ;
private:
    std::vector<Light*> _lights;
    std::vector<Object*> _objects;
    Color _background;
    Color _ambiant;
    SkySphere* _skybox;
};

