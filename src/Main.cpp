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
#include "Objects/Lights/DirectionalLight.h"
#include <algorithm>

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    Scene scene;
    Color specular(1,1,1);

    Material red(Color(1,0, 0),Color(1,0, 0),specular,0.5);
    Material yellow(Color(1,1, 0),Color(1,1, 0),specular,0.3);
    Material green(Color(0,1, 0),Color(0,1, 0),specular,0.1);;
    Material cyan(Color(0,1, 1),Color(0,1, 1),specular,0.1);
    Material blue(Color(0,0, 1),Color(0,0, 1),specular,0.4);
    Material magenta(Color(1,0, 1),Color(1,0, 1),specular,0.1);
    Material black(Color(0,0, 0),Color(0,0, 0),specular,0.1);
    Material white(Color(1, 1, 1), Color(1, 1, 1), specular, 0.1);

    Object* cube = new Cube(Vector(0, 0, 0), Vector(45,45,30), 1.f, green);
    scene.addObject(cube);
    Object* sphere = new Sphere(Vector(2, -0.5, -3),Vector(0,0,90),1.f,red);
    //sphere->rotateX(-90);
    sphere->printTransform();
    scene.addObject(sphere);

    scene.addObject(new Sphere(Vector(-1.9, -0.5, -1), Vector(), 1.0f, white));
    scene.addObject(new Sphere(Vector(2, 2.0, -2.5), Vector(), 0.5f, yellow));
    scene.addObject(new Sphere(Vector(-1.9, 1.9, 0),Vector(),0.85f,blue));

    //scene.addObject(new Carre(Vector(-2, 2, -2), Vector(0, 0, 0), 0.7f, magenta));

    //scene.addObject(new Plan(Vector(-3, -3, -5),Vector(0,-30,0),white));
    //scene.addObject(new Plan(Vector(-3, -3, -4),Vector(0,60,0),white));

    scene.addLight(new DirectionalLight(Vector(0,0,-8),Vector(0,120,45),1, Color(0.1,0.1,0.1), Color(1,1,1), Color(1,1,1)));

    Vector camPos(0,0.5,-7);
    Vector rotation(0,0,0);
    Camera cam(camPos,rotation,24,2.8,8);
    cam.setSensorSize(36,24);

    int height = 500;
    int width = height / 2.0f * 3.0f;

    Image renderImage(width,height, Color(1,0,1));

    Raytracer raytracer;
    raytracer.setCamera(cam);
    raytracer.setBackgroundColor(Color(0,0,0));
    raytracer.setSampleCount(1);

    raytracer.render(scene, renderImage);
    renderImage.save("render");

}