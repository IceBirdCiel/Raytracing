#include <iostream>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"
#include "Rendering/Raytracer.h"
#include "Objects/Sphere.h"
#include "Objects/Cube.h"
#include "Objects/Plane.h"
#include "Objects/Square.h"
#include "Objects/Cylinder.h"
#include "Objects/Camera.h"
#include "Materials/Material.h"
#include "Scene/Scene.h"
#include "Objects/Lights/DirectionalLight.h"
#include "Objects/Lights/PointLight.h"
#include "Rendering/SkySphere.h"
#include <algorithm>
#include <chrono>
#include <memory>


int main(int argc, char** argv) {


    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    auto scene = std::make_shared<Scene>();
    scene->setBackground(Color(0.2, 0.2, 1));
    //SkySphere * skybox = new SkySphere("phalzer_forest_01.png");
    //scene->setSkybox(skybox);

    Color specular(0.75,0.75,0.75);

    Material red(Color(1,0, 0),Color(1,0, 0),specular,50);



    //red.texture = new Image("lena.jpg");
    Material yellow(Color(1,1, 0),Color(1,1, 0),specular,50);
    Material orange(Color(1,0.5, 0),Color(1,0.5, 0),specular,50);
    Material green(Color(0,1, 0),Color(0,1, 0),specular,50);;
    Material cyan(Color(0,1, 1),Color(0,1, 1),specular,50);
    Material blue(Color(0,0, 1),Color(0,0, 1),specular,50);
    blue.texture = new Image("lena.jpg");
    Material magenta(Color(1,0, 1),Color(1,0, 1),specular,50);
    magenta.texture = new Image("lena.png");
    Material black(Color(0,0, 0),Color(0,0, 0),specular,5);
    Material white(Color(1, 1, 1), Color(1, 1, 1), specular, 50);
    Material lena(Color(1, 1, 1), Color(1, 1, 1), specular, 50);
    lena.texture = new Image("lena.png");
    Material grey(Color(0.7, 0.6, 0.7), Color(0.385, 0.385, 0.4), specular, 50);
    Material donoro(Color(0.7, 0.6, 0.7), Color(0.6,0, 0.6), specular, 50);
    donoro.texture = new Image("lena.jpg");


    Material carpet(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    carpet.texture = new Image("carpet.jpg");

    Material wood(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    wood.texture = new Image("wood.jpg");

    Material brick(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    brick.texture = new Image("brick.jpg");

    Material window(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    window.texture = new Image("theWindow.png");

    //walls
    //sol
    scene->addObject(new Plane(Vector(0, -3, 5), Vector(90,-60,0), Vector(10,10,10), wood));
    //mur arriere
    scene->addObject(new Plane(Vector(0, -3, 5), Vector(180,30,0), Vector(3,3,3), brick));
    scene->addObject(new Plane(Vector(-5, -3, 5), Vector(180,-60,0), Vector(3,3,3), brick));
    //ceiling
    scene->addObject(new Plane(Vector(0, 4.5, 5), Vector(90,-60,0), Vector(10,10,10), white));

    //window
    scene->addObject(new Square(Vector(4, 1, 2), Vector(180,30,0), Vector(2.5/8.f*5,2.5,2.5), window));

    scene->addObject(new Sphere(Vector(0, 0, 0), Vector(0,90,90), Vector(1.5,1.5,1.5), lena));
    scene->addObject( new Sphere(Vector(1, -1, -5),Vector(0,90,90),Vector(1,1,1),blue));
    scene->addObject(new Cube(Vector(-5, -2, 3), Vector(0,30,0), Vector(1.f,1.f,1.5f), orange));
    
    scene->addObject(new Cube(Vector(-5, -0.1, 3), Vector(45, 0, 35.264), Vector(0.5f, 0.5f, 0.5f), donoro));
    
    scene->addObject(new Sphere(Vector(1, 2.0, -2.5), Vector(), Vector(0.5,0.5,0.5), orange));
    scene->addObject(new Sphere(Vector(-2, -1.2, -2), Vector(0,90,90), Vector(0.75,0.75,0.75), red));
    scene->addObject(new Sphere(Vector(-1.7, 1.0, 2),Vector(),Vector(0.65f,0.65f,0.65f),magenta));
    scene->addObject(new Sphere(Vector(-0.5, -1.0, -0.7),Vector(),Vector(0.65f,0.65f,0.65f),green));
    scene->addObject(new Sphere(Vector(0.85, -0.7, -2.5),Vector(),Vector(0.35f,0.35f,0.35f),yellow));

    //Carpet
    scene->addObject(new Square(Vector(-1.5, -2.95, 0), Vector(90, 30, 0),Vector(2.f,2.f,2.f), carpet));

    //pillars
    //scene->addObject(new Cylinder(Vector(3, 0, 0), Vector(0, 0, 0), Vector(0.5f,0.5f,0.5f), white));
    //scene->addObject(new Cylinder(Vector(1.5, 0, 3), Vector(0, 0, 0), Vector(0.5f,0.5f,0.5f), white));
    scene->addObject(new Cylinder(Vector(-2, 0, 4.5), Vector(0, 0, 0), Vector(0.5f,0.5f,0.5f), white));
    scene->addObject(new Cylinder(Vector(-6, 3, 3), Vector(90, 30, 0), Vector(0.2f,0.2f,0.2f), red));
    scene->addObject(new Cylinder(Vector(-6, 3.5, 3), Vector(90, 30, 0), Vector(0.2f,0.2f,0.2f), red));

    //scene->addObject(new Plane(Vector(-3, -3, -5),Vector(0,-30,0),white));
    //scene->addObject(new Plane(Vector(-3, -3, -4),Vector(0,60,0),white));

    scene->addLight(new DirectionalLight(Vector(0,0,-8),Vector(0,130,70),1, Color(0.1,0.1,0.1), Color(1,1,1), Color(1,1,1)));

    Vector camPos(0,0.5,-7);
    Vector rotation(5,0,0);
    Camera cam(camPos,rotation,24,5000,6.5);
    cam.setSensorSize(36,24);

    int height = 600;
    int width = height / 2.0f * 3.0f;

    auto renderImage = std::make_shared<Image>(width,height, Color(1,0,1));

    Raytracer raytracer;
    raytracer.setCamera(cam);
    raytracer.setBackgroundColor(Color(0,0,0));
    raytracer.setSampleCount(1);

    std::cout << "\nStarting to render image !\n";
    auto start = std::chrono::high_resolution_clock::now();
    raytracer.render(scene, renderImage);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Image finished rendering!\nRender duration : " << elapsed.count() << " s\n";
    renderImage->save("render");

}