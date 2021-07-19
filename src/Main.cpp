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
    Color diffuse(0,0,0);
    Color specular(1,1,1);

    Material material(ambient,diffuse,specular,0.1);


    Sphere obj(Vector(0, 0, 0),Vector(),1.5f,material);
    Sphere obj2(Vector(1.9, 1.9, 0),Vector(),0.85f,material);
    Sphere obj3(Vector(-1.9, 1.9, 0),Vector(),0.85f,material);


    obj.printTransform();
   // Plan obj(Vector(0, 0, 0),Vector(0, 0, 0), material);
    Vector camPos(0,0.5,-10);
    Vector rotation(0,0,0);
    Camera cam(camPos,rotation,50,50,10);
    cam.setSensorSize(36,24);

    int height = 720;
    int width = height / 2.0f * 3.0f;

    std::cout << "width " << width << " height " << height << std::endl;


    Image renderImage(width,height, Color(1,1,1));

    Ray testray = Ray(Point(0,0,1),Vector(1,0,0));


    std::cout << "Cam pos " << camPos << std::endl;
    cam.printTransform();
    std::cout << std::endl;
    std::cout << "TestRay " << testray << std::endl;
    std::cout << "LocalToGlobal " << cam.localToGlobal(testray) << std::endl;
    std::cout << "LocalToGlobalToLocal " << cam.globalToLocal(cam.localToGlobal(testray)) << std::endl;
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            float viewportX = ((width - x) / ((float)width-1)  * 2) - 1;
            float viewportY = ((height - y) / ((float)height-1) * 2) - 1;

            //std::cout << "Viewport coordinates " << viewportX << ", " << viewportY << std::endl;
            Ray ray = cam.getRay(viewportX,viewportY);
            Point impact;
            if(obj.intersect(ray, impact)){
                renderImage.setColor(x,y,obj.getMaterial(impact).kd);
            }else if(obj2.intersect(ray, impact)){
                renderImage.setColor(x,y,obj2.getMaterial(impact).kd);
            }else if(obj3.intersect(ray, impact)){
                renderImage.setColor(x,y,obj3.getMaterial(impact).kd);
            }
        }
    }
    renderImage.save("render");

}