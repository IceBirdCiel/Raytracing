    #include <iostream>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"
#include "Objects/Sphere.h"
#include "Objects/Plan.h"
#include "Objects/Camera.h"
#include "Materials/Material.h"
#include "Scene/Scene.h"

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    Scene scene;

    Color ambient(0.2,0.2,0);
    Color diffuse(0,0,0);
    Color specular(1,1,1);

    Material material(ambient,diffuse,specular,0.1);

    scene.addObject(Sphere(Vector(0, 0, 0),Vector(),1.5f,material));
    scene.addObject(Sphere(Vector(1.9, 1.9, 0),Vector(),0.85f,material));
    scene.addObject(Sphere(Vector(-1.9, 1.9, 0),Vector(),0.85f,material));

    Vector camPos(0,0.5,-10);
    Vector rotation(0,0,0);
    Camera cam(camPos,rotation,50,50,10);
    cam.setSensorSize(36,24);

    int height = 720;
    int width = height / 2.0f * 3.0f;

    Image renderImage(width,height, Color(1,1,1));

    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            float viewportX = ((width - x) / ((float)width-1)  * 2) - 1;
            float viewportY = ((height - y) / ((float)height-1) * 2) - 1;

            //std::cout << "Viewport coordinates " << viewportX << ", " << viewportY << std::endl;
            Ray ray = cam.getRay(viewportX,viewportY);
            Point impact;
            Sphere sphere;
            if(scene.closestObjectIntersected(ray,sphere,impact)){
                renderImage.setColor(x,y,sphere.getMaterial(impact).kd);
            }
        }
    }
    renderImage.save("render");

}