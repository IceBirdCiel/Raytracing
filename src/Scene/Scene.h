#pragma once

#include <vector>
#include "../Materials/Color.h"
#include "../Objects/Lights/Light.h"
#include "../Objects/Sphere.h"
#include "../Rendering/Image.h"
#include "../Rendering/SkySphere.h"
#include "../Objects/Camera.h"

class Scene
{
public:
    Scene(){
        _skySphere = nullptr;
    };
    ~Scene();
    Color getBackground(const Ray& ray) const;
    Color getAmbiant() const;

    void setAmbiant(Color color);
    void setBackground(Color color);
    void setSkybox(SkySphere* skybox);

    int nbLights() const;
    [[nodiscard]] Light* getLight(int index) const;
    void addLight(Light* light);
    void addObject(Object* object);
    Object* closestObjectIntersected(Ray ray, Point& closestImpact) const;
    Camera* camera;
private:
    std::vector<Light*> _lights;
    std::vector<Object*> _objects;
    Color _background;
    Color _ambient;
    SkySphere* _skySphere;
};

