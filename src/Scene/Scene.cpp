#include "Scene.h"

void Scene::setBackground(Color color)
{
    _background = color;
}

void Scene::setAmbiant(Color color)
{
    _ambient = color;
}

Color Scene::getBackground(const Ray& ray) const
{
    if(_skySphere != nullptr){
        Point impact;
        if(_skySphere->intersect(ray, impact)){
            Ray normal = _skySphere->getNormals(impact, ray.origin);
            Point texCoords = _skySphere->getTextureCoordinates(normal.origin);
            Material material = _skySphere->getMaterial(impact);
            int x = texCoords[0] * (material.texture->getWidth() - 1);
            int y = texCoords[1] * (material.texture->getHeight() - 1);
            return material.texture->getColor(x, y);
        }
    }
    return _background;
}

Color Scene::getAmbiant() const
{
    return _ambient;
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
    float distance = FLT_MAX;
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

void Scene::setSkybox(SkySphere *skybox) {
    _skySphere = skybox;
}

Scene::~Scene() {
    delete camera;
    delete _skySphere;
}
