#include "Scene.h"

void Scene::setBackground(Color color)
{
    _background = color;
}

void Scene::setAmbiant(Color color)
{
    _ambiant = color;
}

Color Scene::getBackground() const
{
    return _background;
}

Color Scene::getAmbiant() const
{
    return _ambiant;
}

int Scene::nbLights() const
{
    return _lights.size();
}

const Light Scene::getLight(int index) const
{
    return _lights[index];
}
void Scene::addLight(Light light)
{
    _lights.emplace_back(light);
}

void Scene::addObject(Sphere object) {
    _objects.emplace_back(object);
}

bool Scene::closestObjectIntersected(Ray ray, Sphere& object, Point& closestImpact) const {
    float distance = INT8_MAX;
    Point impact;
    bool hit = false;
    for (int i = 1; i < _objects.size(); ++i) {
        Sphere obj = _objects[i];
        if(obj.intersect(ray, impact)){
            hit = true;
            Vector diff(ray.origin[0] - impact[0], ray.origin[1] - impact[1], ray.origin[2] - impact[2]);
            float dist = diff.norm();
            if(dist < distance){
                object = obj;
                distance = dist;
                closestImpact = impact;
            }
        }
    }
    return hit;
}
