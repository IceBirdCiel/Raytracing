#pragma once
#include "../Objects/Camera.h"
#include "Image.h"
#include "../Scene/Scene.h"
#include "../Materials/Color.h"

class Raytracer
{
public:
    Raytracer();
    void setCamera(const Camera& cam);
    void setBackgroundColor(Color c);
    void setSampleCount(int samples);
    void render(const Scene& scene, Image& image);
private:

    Color getColorForRay(Ray ray, const Scene& scene) const;
    [[nodiscard]] float InterleavedGradientNoise(float x, float y) const;

    Camera _camera;
    Color _backgroundColor;
    int _sampleCount;

};
