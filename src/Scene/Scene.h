#pragma once

#include <vector>
#include "../Materials/Color.h"
#include "../Objects/Light.h"

class Scene
{
public:
    Color getBackground() const;
    Color getAmbiant() const;

    void setAmbiant(Color color);
    void setBackground(Color color);

    int nbLights() const;
    const Light* getLight(int index) const;
    void addLight(Light* light);
    // todo object* closer_intersected
private:
    std::vector<Light*> _lights;
    Color _background;
    Color _ambiant;
};

