#include "Raytracer.h"
#include <thread>
#include <utility>
#include <omp.h>

Raytracer::Raytracer(){}

void Raytracer::render(std::shared_ptr<Scene> scene, std::shared_ptr<Image>& image, int ssaa, bool enableShadows){

    /*int pixelsAmount = height*width;
    int pixelsProcessed = 0;
    float progress = 0;
    int barWidth = 70;*/
    _scene = std::move(scene);
    _renderImage = image;
    int width = image->getWidth();
    int height = image->getHeight();
    int sampleCount = _scene->camera->getSampleCount();
    #pragma omp parallel for
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){

            float pixelR = 0;
            float pixelG = 0;
            float pixelB = 0;

            //for loop for super sampling anti aliasing
            for (int subX = 0; subX < ssaa; ++subX) {
                for (int subY = 0; subY < ssaa; ++subY) {
                    //conversion from screen space to view space
                    float viewportX = ((x+ ((float)subX/(float)ssaa)) / ((float)width-1)  * 2) - 1;//+ 1/(float)subX
                    float viewportY = ((height - y + ((float)subY/(float)ssaa)) / ((float)height-1) * 2) - 1;// + 1/(float)subY

                    float r = 0;
                    float g = 0;
                    float b = 0;

                    float random = InterleavedGradientNoise(x,y);
                    _scene->camera->setupForRay(sampleCount,random);
                    //multisampling
                    for (int i = 0; i < sampleCount; ++i) {
                        Ray ray = _scene->camera->getRay(viewportX,viewportY, i);
                        Color c = getColorForRay(ray,_scene,enableShadows);
                        r += c.r;
                        g += c.g;
                        b += c.b;
                    }
                    pixelR += r/sampleCount;
                    pixelG += g/sampleCount;
                    pixelB += b/sampleCount;
                }
            }

            int subSamplesCount = ssaa*ssaa;
            pixelR = pixelR/(float)subSamplesCount;
            pixelG = pixelG/(float)subSamplesCount;
            pixelB = pixelB/(float)subSamplesCount;

            //on calcule la couleur finale en faisant la moyenne des couleurs obtenues
            _renderImage->setColor(x,y,Color(pixelR,pixelG,pixelB));
            _renderImage->setColor(x,y,Color(pixelR,pixelG,pixelB));

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
    /*
    int width = image->getWidth();
    int height = image->getHeight();

    std::thread th1(thread_renderer(),1);// 0, 0, width/2,height/2, width, height, _sampleCount, std::ref(_camera), std::ref(_scene), std::ref(_renderImage));
    std::thread th2(thread_renderer(),2);// width/2, 0, width,height/2, width, height, _sampleCount, std::ref(_camera), std::ref(_scene), std::ref(_renderImage));
    std::thread th3(thread_renderer(),3);
    std::thread th4(thread_renderer(),4);
    th1.join();
    th2.join();
    th3.join();
    th4.join();*/
}

Color Raytracer::getColorForRay(Ray ray, const std::shared_ptr<Scene>& scene, bool enableShadows) const {
    Color finalColor(0,0,0);
    float r = 0;
    float g = 0;
    float b = 0;
    Point impact;
    Object* obj = scene->closestObjectIntersected(ray,impact);
    if(obj != nullptr){
        //std::cout << "collide" << std::endl;

        Ray normal = obj->getNormals(impact,ray.origin);
        Material material = obj->getMaterial(impact);

        for (int i = 0; i < scene->nbLights(); ++i) {
            Light* light = scene->getLight(i);
            Point temp = impact - light->getPosition();
            Ray lightRay = Ray(light->getPosition(), Vector(temp[0],temp[1],temp[2]).normalized());
            Point tempImpact;
            bool shadow = false;
            if(enableShadows) shadow = obj != scene->closestObjectIntersected(lightRay,tempImpact);

            Color phongColor = getPhong(light, shadow, normal.normalized(),_scene->camera->forward(), material, *obj);
            r += phongColor.r;
            g += phongColor.g;
            b += phongColor.b;
        }
        finalColor = Color(r,g,b);
    } else {
        finalColor = scene->getBackground(ray);
    }
    return finalColor;
}

float Raytracer::InterleavedGradientNoise(float x, float y) const {
    Vector pos(x*10,y*10,0);
    Vector magic = Vector(0.06711056, 0.00583715, 52.9829189);
    double integralPart = 0;
    return modf(magic[0] * modf(pos.dot(Vector(magic[0],magic[1],magic[2])), &integralPart), &integralPart);
}

Color Raytracer::getLambert(Light* light, bool shadow, const Ray& normal, const Material& material,
                            const Object& obj) const {

    Vector dir;
    float attenuation = light->getLightingBehaviour(normal,dir);
    Color ambiant = material.ambient * light->Ambient() * attenuation * light->intensity;
    Color diffuse = Color(0,0,0);
    if(!shadow){
        float angle = normal.vector.normalized().dot(dir);

        diffuse = Color(1,1,1);
        if(material.texture != nullptr){
            Point texCoords = obj.getTextureCoordinates(normal.origin);
            int x = texCoords[0] * (material.texture->getWidth() - 1);
            int y = texCoords[1] * (material.texture->getHeight() - 1);
            Color pixelColor = material.texture->getColor(x, y);
            //std::cout << pixelColor.r << ", " << pixelColor.g << ", "  << pixelColor.b << std::endl;
            diffuse = pixelColor;
        }
        diffuse = diffuse * material.diffuse * light->Diffuse() * angle * attenuation  * light->intensity;
    }
    Color lambert = ambiant + diffuse;

    return lambert;
    return Color();
}

Color Raytracer::getPhong(Light* light, bool shadow, const Ray& normal, Vector cameraForward, const Material& material,
                          const Object& obj) const {
    Vector dir;

    float attenuation = light->getLightingBehaviour(normal,dir);

    Color lambert = getLambert(light, shadow, normal, material, obj);
    Color phong = lambert;
    if(!shadow){
        //Vector reflect = dir - normal.vector * ( 2 * dir.dot(normal.vector));
        Vector reflect = normal.vector.normalized().reflect(dir);
        //float spec = pow(material.shininess, cameraForward.dot(reflect));
        float spec = pow(std::max(cameraForward.dot(reflect), 0.f), material.shininess);
        //spec = (spec < 0) ? 0 : spec;
        Color specular = material.specular * light->Specular() * spec * attenuation  * light->intensity;
        phong = phong + specular;
    }

    return phong;
}
