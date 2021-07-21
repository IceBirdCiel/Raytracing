#include "Scene.h"

void Scene::setBackground(Color color)
{
    _background = color;
}

void Scene::setAmbiant(Color color)
{
    _ambiant = color;
}

Color Scene::getBackground(const Ray& ray) const
{
    if(_skybox != nullptr){
        return _skybox->getColor(ray);
    }
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

Light* Scene::getLight(int index) const
{
    return _lights[index];
}
void Scene::addLight(Light* light)
{
    _lights.emplace_back(light);
}

void Scene::addObject(Object* object) {
    _objects.emplace_back(object);
}

Object* Scene::closestObjectIntersected(Ray ray, Point& closestImpact) const {
    float distance = INT16_MAX;
    Object* Lior = nullptr;
    Point impact;
    bool collisionDetected = false;
    for (int i = 0; i < _objects.size(); ++i) {
        Object* objectToIntersect = _objects[i];
        if(objectToIntersect->intersect(ray, impact)){
            Vector diff(ray.origin[0] - impact[0], ray.origin[1] - impact[1], ray.origin[2] - impact[2]);
            float dist = diff.norm();
            if(dist < distance){
                Lior = objectToIntersect;
                closestImpact = impact;

                distance = dist;
            }
            collisionDetected = true;
        }
    }
    if(collisionDetected){
        return Lior;
    }else{
        return nullptr;
    }
}

void Scene::setSkybox(Skybox *skybox) {
    _skybox = skybox;
}
