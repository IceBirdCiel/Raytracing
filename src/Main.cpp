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
#include "Objects/Cone.h"
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
    Material grey(Color(0.7, 0.6, 0.7), Color(0.385, 0.385, 0.4), specular, 50);
    Material lena(Color(0,0,0), Color(1,1,1), specular, 50);
    lena.texture = new Image("lena.jpg");


    Material earth(Color(0, 0, 0), Color(1, 1, 1), specular, 75);
    earth.texture = new Image("earth.jpg");

    Material mars(Color(0, 0, 0), Color(1, 1, 1), specular, 25);
    mars.texture = new Image("mars.jpg");
    Material football(Color(1,1,1), Color(1, 1, 1), specular, 15);
    football.texture = new Image("football.png");
    Material tennis(Color(1,1,1), Color(1, 1, 1), specular, 100);
    tennis.texture = new Image("tennis.png");
    Material weirdbluesphere(Color(1,1,1), Color(1, 1, 1), specular, 100);
    weirdbluesphere.texture = new Image("weirdbluesphere.jpg");

    Material carpet(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    carpet.texture = new Image("carpet.jpg");

    Material wood(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    wood.texture = new Image("wood.jpg");

    Material brick(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    brick.texture = new Image("brick.jpg");

    Material window(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    window.texture = new Image("theWindow2.png");

    Material uv(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    uv.texture = new Image("uv.png");

    Material portal(Color(1, 1, 1), Color(1, 1, 1), specular, 1);
    portal.texture = new Image("portal.png");

    //walls
    //sol
    scene->addObject(new Plane(Vector(0, -3, 5), Vector(90,-60,0), Vector(10,10,10), wood));
    //mur arriere
    scene->addObject(new Plane(Vector(0, -3, 5), Vector(180,30,0), Vector(3,3,3), brick));
    scene->addObject(new Plane(Vector(-5, -3, 5), Vector(180,-60,0), Vector(3,3,3), brick));
    //ceiling
    scene->addObject(new Plane(Vector(0, 4.5, 5), Vector(90,-60,0), Vector(10,10,10), white));

    //Object* cone = new Cone(Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), white);
    //scene->addObject(cone);
    //cone->printTransform();

    //window
    scene->addObject(new Square(Vector(4, 1, 2), Vector(180,30,0), Vector(2.5/8.f*5,2.5,2.5), window));

    //planets
    scene->addObject(new Sphere(Vector(0, 0, 0), Vector(0,90,90), Vector(1.5,1.5,1.5), earth));
    scene->addObject(new Sphere(Vector(-2, -1.2, -2), Vector(0,90,90), Vector(0.75,0.75,0.75), mars));

    //football
    scene->addObject(new Sphere(Vector(1, 1.5, -2.5), Vector(90,45,0), Vector(0.5,0.5,0.5), football,tennis,4));

    //tennis
    scene->addObject(new Sphere(Vector(0.85, -0.7, -2.5),Vector(),Vector(0.35f,0.35f,0.35f),tennis));

    //weird blue sphere
    scene->addObject( new Sphere(Vector(1, -1, -5),Vector(0,90,90),Vector(1,1,1),football));

    scene->addObject(new Cube(Vector(-5, -2, 3), Vector(0,30,0), Vector(1.f,1.f,1.5f), orange));
    
    scene->addObject(new Cube(Vector(-5, -0.1, 3), Vector(45, 0, 35.264), Vector(0.5f, 0.5f, 0.5f), portal));

    scene->addObject(new Sphere(Vector(-1.9, 1.0, 2),Vector(0,90,90),Vector(0.65f,0.65f,0.65f),lena));
    //
    scene->addObject(new Sphere(Vector(-0.5, -1.0, -0.7),Vector(90,45,0),Vector(0.65f,0.65f,0.65f),weirdbluesphere));

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

    scene->addLight(new DirectionalLight(Vector(0,1,-1.5),Vector(0,130,70),1, Color(0.1,0.1,0.1), Color(1,1,1), Color(1,1,1)));

    Vector camPos(0,0.5,-7);
    Vector rotation(5,0,0);
    Camera cam(camPos,rotation,24,5000,6.5);
    cam.setSensorSize(36,24);

    int height = 600;
    int width = height / 2.0f * 3.f;

    auto renderImage = std::make_shared<Image>(width,height, Color(1,0,1));

    Raytracer raytracer;
    raytracer.setCamera(cam);
    raytracer.setBackgroundColor(Color(0,0,0));
    raytracer.setSampleCount(1);

    std::cout << "\nStarting to render image !\n";
    auto start = std::chrono::high_resolution_clock::now();
    raytracer.render(scene, renderImage,2);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Image finished rendering!\nRender duration : " << elapsed.count() << " s\n";
    renderImage->save("render");

}