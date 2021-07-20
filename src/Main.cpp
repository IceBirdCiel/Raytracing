#include <iostream>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"
#include "Rendering/Raytracer.h"
#include "Objects/Sphere.h"
#include "Objects/Cube.h"
#include "Objects/Plan.h"
#include "Objects/Carre.h"
#include "Objects/Camera.h"
#include "Materials/Material.h"
#include "Scene/Scene.h"
#include <algorithm>

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    Scene scene;

    Color ambient(0,0,0);
    Color specular(1,1,1);

    Material red(ambient,Color(1,0, 0),specular,1);
    Material yellow(ambient,Color(1,1, 0),specular,1);
    Material green(ambient,Color(0,1, 0),specular,0.1);;
    Material cyan(ambient,Color(0,1, 1),specular,0.1);
    Material blue(ambient,Color(0,0, 1),specular,0.1);
    Material magenta(ambient,Color(1,0, 1),specular,0.1);
    Material black(ambient,Color(0,0, 0),specular,0.1);
    Material white(ambient, Color(1, 1, 1), specular, 0.1);

    Object* cube = new Cube(Vector(0, -1, 0), Vector(50,0,0), 1.f, green);
    scene.addObject(cube);
    scene.addObject(new Sphere(Vector(1.2, -0.5, -3),Vector(),1.5f,red));
    scene.addObject(new Carre(Vector(0, 0, -1),Vector(),1.f,magenta));
    scene.addObject(new Plan(Vector(0, 0, -2),Vector(-90,0,0),white));
    scene.addObject(new Sphere(Vector(-1.9, -0.5, -1), Vector(), 1.0f, white));
    scene.addObject(new Sphere(Vector(2, 2.0, -2.5), Vector(), 0.5f, yellow));
    scene.addObject(new Sphere(Vector(-1.9, 1.9, 0),Vector(),0.85f,blue));

    scene.addLight(Light(Vector(0,8,-5),Vector(),1, Color(0,0,0), Color(1,1,1), Color(1,1,1)));

    Vector camPos(0,0.5,-8);
    Vector rotation(0,0,0);
    Camera cam(camPos,rotation,35,5000,8);
    cam.setSensorSize(36,24);

    int height = 300;
    int width = height / 2.0f * 3.0f;

    Image renderImage(width,height, Color(1,0,1));

    Raytracer raytracer;
    raytracer.setCamera(cam);
    raytracer.setBackgroundColor(Color(0,0,0));
    raytracer.setSampleCount(1);

    raytracer.render(scene, renderImage);
    renderImage.save("render");

}