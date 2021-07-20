#include "Raytracer.h"

Raytracer::Raytracer(): _camera(Camera(Vector(0,0,-10),Vector(),24,2.8,10)), _sampleCount(1) {}

void Raytracer::setCamera(const Camera& cam) {
_camera = cam;
}

void Raytracer::render(const Scene& scene, Image& image) const{

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

            //multisampling
            for (int i = 0; i < _sampleCount; ++i) {
                Ray ray = _camera.getRay(viewportX,viewportY);
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
    Color finalColor = _backgroundColor;
    Point impact;
    Object* obj = scene.closestObjectIntersected(ray,impact);
    if(obj != nullptr){
        //std::cout << "collide" << std::endl;

        /*for (int i = 0; i < scene.nbLights(); ++i) {

        }*/

        Ray normal = obj->getNormals(impact,ray.origin);
        Material material = obj->getMaterial(impact);


        Light l = scene.getLight(0);
        float lightConstant = 0.1f;
        float lightLinear = 1.0f;
        float lightQuadratic = 0.3f;

        //SPOT LIGHT LIGHTING
        //NEEDS TO END UP INSIDE OF RAYTRACER CLASS OR AT LEAST IN A FUNCTION

        Vector impactPos(normal.origin[0],normal.origin[1],normal.origin[2]);
        Vector lightDir = (l.getPosition() - impactPos).normalized();
        // diffuse shading
        float diff = std::max(normal.vector.dot(lightDir), 0.0f);
        // specular shading

        Vector reflectDir = -lightDir - normal.vector * (2 * lightDir.dot(normal.vector));

        float spec = pow(std::max(_camera.forward().dot(reflectDir), 0.0f), material.shininess);
        // attenuation
        float distance    = (l.getPosition() - impactPos).norm();
        float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
        // combine results
        Color ambient  = l.ambient * material.diffuse; //vec3(texture(material.diffuse, TexCoords));
        Color diffuse  = l.diffuse * material.diffuse;//l.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
        //Todo: add the specular coeff
        Color specular = l.specular * material.specular;//l.specular * spec * vec3(texture(material.specular, TexCoords));
        ambient  = ambient * attenuation;
        diffuse  = diffuse * attenuation;
        specular  = specular * attenuation;
        finalColor = (ambient + diffuse + specular);
    }
    return finalColor;
}

void Raytracer::setBackgroundColor(Color c) {
    _backgroundColor = c;
}

void Raytracer::setSampleCount(int samples) {
    _sampleCount = samples;
}

