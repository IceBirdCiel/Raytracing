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
    void render(std::shared_ptr<Scene> scene, std::shared_ptr<Image> image);
private:

    Color getColorForRay(Ray ray, std::shared_ptr<Scene> scene) const;
    [[nodiscard]] float InterleavedGradientNoise(float x, float y) const;
    void renderZone(int minX, int minY,int maxX,int maxY, int width, int height);

    Camera _camera;
    Color _backgroundColor;
    int _sampleCount;
    std::shared_ptr<Scene> _scene;
    std::shared_ptr<Image> _renderImage;

};
