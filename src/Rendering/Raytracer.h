#pragma once
#include "../Objects/Camera.h"
#include "Image.h"
#include "../Scene/Scene.h"
#include "../Materials/Color.h"

class Raytracer
{
public:
    Raytracer();
    void setSampleCount(int samples);
    void render(std::shared_ptr<Scene> scene, std::shared_ptr<Image>& image, int ssaa);
    Color getLambert(Light*  light, bool shadow, const Ray& normal, const Material& material, const Object& obj) const;
    Color getPhong(Light*  light, bool shadow, const Ray& normal,Vector cameraForward, const Material& material, const Object& obj) const;
private:

    Color getColorForRay(Ray ray, const std::shared_ptr<Scene>& scene) const;
    [[nodiscard]] float InterleavedGradientNoise(float x, float y) const;
    void renderZone(int minX, int minY,int maxX,int maxY, int width, int height);

    int _sampleCount;
    std::shared_ptr<Scene> _scene;
    std::shared_ptr<Image> _renderImage;

};
