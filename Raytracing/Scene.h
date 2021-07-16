#pragma once

#include <vector>
#include "Color.h"
#include "Light.h"

class Scene
{
public:
	Color getBackground() const;
	Color getAmbiant() const;
	int nbLights() const;
	const Light* getLight(int index) const;
	void addLight(Light* light);
	// todo object* closer_intersected
private:
	std::vector<Light*> _lights;
	Color _background;
	Color _ambiant;
};

