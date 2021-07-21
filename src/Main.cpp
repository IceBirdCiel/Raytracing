#include <iostream>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"
#include "Objects/Sphere.h"
#include "Objects/Plan.h"
#include "Objects/Camera.h"
#include "Materials/Material.h"
#include "Scene/Scene.h"
#include "Rendering/Skybox.h"
#include <algorithm>

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    Scene scene;
    scene.setBackground(Color(0.2, 0.2, 1));
    Skybox skybox("phalzer_forest_01.png");

    Color ambient(0.2,0.2,0);
    Color diffuse(1,0,0);
    Color diffuse2(0,1,0);
    Color diffuse3(0,0,1);
    Color specular(1,1,1);

    Material red(ambient,diffuse,specular,1);
    Material green(ambient,diffuse2,specular,0.1);
    Material blue(ambient,diffuse3,specular,0.1);

    scene.addObject(Sphere(Vector(0, 0, 0),Vector(),1.5f,green));
    scene.addObject(Sphere(Vector(1.9, 1.9, 0),Vector(),0.85f,red));
    scene.addObject(Sphere(Vector(-1.9, 1.9, 0),Vector(),0.85f,blue));

    scene.addLight(Light(Vector(0,4,-2),Vector(),1, Color(1,1,1), Color(1,1,1), Color(1,1,1)));

    Vector camPos(0,0.5,-13);
    Vector rotation(0,0,0);
    Camera cam(camPos,rotation,50,50,10);
    cam.setSensorSize(36,24);

    int height = 480;
    int width = height / 2.0f * 3.0f;

    Image renderImage(width,height, Color(1,1,1));

    int pixelsAmount = height*width;
    int pixelsProcessed = 0;
    float progress = 0;
    int barWidth = 70;
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            float viewportX = ((width - x) / ((float)width-1)  * 2) - 1;
            float viewportY = ((height - y) / ((float)height-1) * 2) - 1;

            //std::cout << "Viewport coordinates " << viewportX << ", " << viewportY << std::endl;
            Ray ray = cam.getRay(viewportX,viewportY);
            Point impact;
            Sphere sphere;
            if(scene.closestObjectIntersected(ray,sphere,impact)){
                //std::cout << "collide" << std::endl;

                /*for (int i = 0; i < scene.nbLights(); ++i) {

                }*/

                Ray normal = sphere.getNormals(impact,ray.origin);
                Material material = sphere.getMaterial(impact);


                Light l = scene.getLight(0);
                float lightConstant = 1.0f;
                float lightLinear = 2.0f;
                float lightQuadratic = 2.0f;

                //SPOT LIGHT LIGHTING
                //NEEDS TO END UP INSIDE OF RAYTRACER CLASS OR AT LEAST IN A FUNCTION

                Vector impactPos(normal.origin[0],normal.origin[1],normal.origin[2]);
                Vector lightDir = (l.getPosition() - impactPos).normalized();
                // diffuse shading
                float diff = std::max(normal.vector.dot(lightDir), 0.0f);
                // specular shading

                Vector reflectDir = -lightDir - normal.vector * (2 * lightDir.dot(normal.vector));


                float spec = pow(std::max(cam.forward().dot(reflectDir), 0.0f), material.shininess);
                // attenuation
                float distance    = (l.getPosition() - impactPos).norm();
                float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));
                // combine results
                Color ambient  = l.ambient * material.diffuse; //vec3(texture(material.diffuse, TexCoords));
                Color diffuse  = l.diffuse * material.diffuse;//l.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
                Color specular = l.specular * material.specular;//l.specular * spec * vec3(texture(material.specular, TexCoords));
                ambient  = ambient * attenuation;
                diffuse  = diffuse * attenuation;
                specular  = specular * attenuation;
                Color finalColor = (ambient + diffuse + specular);




                //std::cout << normal << std::endl;
                renderImage.setColor(x,y,finalColor);
            } else {
                // plain color
                //renderImage.setColor(x, y, scene.getBackground());

                // skybox
                renderImage.setColor(x, y, skybox.getColor(ray));
            }
            pixelsProcessed++;
        }

        progress = pixelsProcessed / (float)pixelsAmount;
        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "|";
            else if (i == pos) std::cout << " ";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();
    }
    renderImage.save("render");
}