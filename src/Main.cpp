#include <iostream>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"
#include "Objects/Sphere.h"
#include "Objects/Camera.h"
#include "Materials/Material.h"

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    Color ambient(0.2,0.2,0);
    Color diffuse(1,0.,1);
    Color specular(1,1,1);

    Material material(ambient,diffuse,specular,0.1);
    Sphere sphere(0.5f,Vector(0,2,0),material);

    Vector camPos(0,0,0);
    Vector rotation(0,0,0);
    Camera cam(camPos,rotation,24,50,2);

    Image renderImage(128,128, Color(0.5,0.5,0.5));

    Color hit(1,0,0);
    for(int y = 0; y < 128; ++y){
        for(int x = 0; x < 128; ++x){
            Ray ray = cam.getRay(x/128*2-1,y/128*2-1);
            Point impact;
            if(sphere.intersect(ray, impact)){
                renderImage.setColor(x,y,hit);
            }
        }
    }
    renderImage.save("render");

}