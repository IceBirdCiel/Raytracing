    #include <iostream>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"
#include "Objects/Sphere.h"
#include "Objects/Plan.h"
#include "Objects/Camera.h"
#include "Materials/Material.h"

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    Color ambient(0.2,0.2,0);
    Color diffuse(1,0.,1);
    Color specular(1,1,1);

    Material material(ambient,diffuse,specular,0.1);
    Sphere obj(0.5f, Vector(0, 2, 0), material);
   // Plan obj(Vector(0, 0, 0),Vector(0, 0, 0), material);
    Vector camPos(0,2,0);
    Vector rotation(45,0,0);
    Camera cam(camPos,rotation,5,50,10);
    cam.setSensorSize(24,32);

    int width = 16;
    int height = 16;
    Image renderImage(width,height, Color(0,0,0));

    Ray testray = Ray(Point(0,0,1),Vector(0,0,1));

    std::cout << "TestRay " << testray << std::endl;;
    std::cout << "LocalToGlobal " << cam.localToGlobal(testray) << std::endl;
    std::cout << "LocalToGlobalToLocal " << cam.globalToLocal(cam.localToGlobal(testray)) << std::endl;
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            float viewportX = (x / ((float)width-1)  * 2) - 1;
            float viewportY = (y / ((float)height-1) * 2) - 1;

            //std::cout << "Viewport coordinates " << viewportX << ", " << viewportY << std::endl;
            Ray ray = cam.getRay(viewportX,viewportY);
            Point impact;
            if(obj.intersect(ray, impact)){
                renderImage.setColor(x,y,obj.getMaterial(impact).kd);
            }
        }
    }
    renderImage.save("render");

}