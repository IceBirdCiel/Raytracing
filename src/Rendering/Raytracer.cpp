#include "Raytracer.h"

Raytracer::Raytracer(): _camera(Camera(Vector(0,0,-10),Vector(),24,2.8,10)), _sampleCount(1) {}

void Raytracer::setCamera(const Camera& cam) {
_camera = cam;
}

void Raytracer::render(const Scene& scene, Image& image){

    /*int pixelsAmount = height*width;
    int pixelsProcessed = 0;
    float progress = 0;
    int barWidth = 70;*/

    int width = image.getWidth();
    int height = image.getHeight();
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){

            //conversion from screen space to view space
            float viewportX = (x / ((float)width-1)  * 2) - 1;
            float viewportY = ((height - y) / ((float)height-1) * 2) - 1;

            float r = 0;
            float g = 0;
            float b = 0;

            float random = InterleavedGradientNoise(x,y);
            _camera.setupForRay(_sampleCount,random);
            //multisampling
            for (int i = 0; i < _sampleCount; ++i) {
                Ray ray = _camera.getRay(viewportX,viewportY, i);
                Color c = getColorForRay(ray,scene);
                r += c.r;
                g += c.g;
                b += c.b;
            }
            //on calcule la couleur finale en faisant la moyenne des couleurs obtenues
            image.setColor(x,y,Color(r/(float)_sampleCount,g/(float)_sampleCount,b/(float)_sampleCount));
            //pixelsProcessed++;
        }
        /*
        progress = pixelsProcessed / (float)pixelsAmount;
        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "|";
            else if (i == pos) std::cout << " ";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();*/
    }
}

Color Raytracer::getColorForRay(Ray ray, const Scene& scene) const {
    Color finalColor(0,0,0);
    Point impact;
    Object* obj = scene.closestObjectIntersected(ray,impact);
    if(obj != nullptr){
        //std::cout << "collide" << std::endl;

        Ray normal = obj->getNormals(impact,ray.origin);
        Material material = obj->getMaterial(impact);

        for (int i = 0; i < scene.nbLights(); ++i) {
            Light* light = scene.getLight(i);
            finalColor = finalColor + light->getPhong(normal.normalized(),_camera.forward(), material, *obj);
        }

        Light* l = scene.getLight(0);

    } else {
        finalColor = scene.getBackground(ray);
    }
    return finalColor;
}

void Raytracer::setBackgroundColor(Color c) {
    _backgroundColor = c;
}

void Raytracer::setSampleCount(int samples) {
    _sampleCount = samples;
}

float Raytracer::InterleavedGradientNoise(float x, float y) const {
    Vector pos(x*10,y*10,0);
    Vector magic = Vector(0.06711056, 0.00583715, 52.9829189);
    double integralPart = 0;
    return modf(magic[0] * modf(pos.dot(Vector(magic[0],magic[1],magic[2])), &integralPart), &integralPart);
}
