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

const Light* Scene::getLight(int index) const
{
    return _lights[index];
}

void Scene::addLight(Light* light)
{
    _lights.emplace_back(light);
}
