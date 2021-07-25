
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
#include "Serialization/FileLoader.h"
#include <algorithm>
#include <chrono>
#include "Setup.h"

int main(int argc, char** argv) {
    //                   THE REAL SHIT

    Setup::setupRenderer();


    //auto scene = FileLoader::loadScene("resources/serialized/Scene1.scene");
    //SkySphere * skybox = new SkySphere("phalzer_forest_01.png");
    //scene->setSkybox(skybox);


    /*Color ambient = Color(0.05, 0.05, 0.05);
    Color specular(1,1,1);

    Material red(ambient, Color(1, 0, 0), specular, 200);

    Material orange(ambient, Color(1, 0.5, 0), specular, 50);
    Material white(ambient, Color(1, 1, 1), specular, 5);
    Material lena(ambient, Color(1, 1, 1), specular, 200);
    Image *lenaTex = new Image("lena.png");
    //lenaTex->convertToLinear();
    lena.texture = lenaTex;


    Material earth(ambient, Color(1, 1, 1), specular, 100);
    earth.texture = new Image("earth.jpg");
    //earth.texture->convertToLinear();

    Material mars(ambient, Color(1, 1, 1), specular, 5);
    mars.texture = new Image("mars.jpg");
    //mars.texture->convertToLinear();
    Material football(ambient, Color(1, 1, 1), specular, 35);
    football.texture = new Image("football.png");
    //football.texture->convertToLinear();
    Material tennis(ambient, Color(1, 1, 1), specular, 100);
    tennis.texture = new Image("tennis.png");
    //tennis.texture->convertToLinear();
    Material weirdbluesphere(ambient, Color(1, 1, 1), specular, 100);
    weirdbluesphere.texture = new Image("weirdbluesphere.jpg");
    //weirdbluesphere.texture->convertToLinear();

    Material carpet(ambient, Color(1, 1, 1), specular, 1);
    carpet.texture = new Image("carpet.jpg");
    //carpet.texture->convertToLinear();

    Material wood(ambient, Color(1, 1, 1), specular, 1);
    wood.texture = new Image("wood.jpg");
    //wood.texture->convertToLinear();

    Material brick(ambient, Color(1, 1, 1), specular, 100);
    brick.texture = new Image("brick.jpg");
    //brick.texture->convertToLinear();

    Material window(ambient, Color(1, 1, 1), specular, 100);
    window.texture = new Image("theWindow2.png");
    //window.texture->convertToLinear();

    Material portal(ambient, Color(1, 1, 1), specular, 1);
    portal.texture = new Image("portal.png");
    //portal.texture->convertToLinear();

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
    scene->addObject(new Sphere(Vector(1, 1.0, -2), Vector(0,90,90), Vector(0.3,0.3,0.3), football,tennis,4));

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
    scene->addObject(new Cylinder(Vector(-2, 0, 4.5), Vector(0, 0, 0), Vector(0.5f,0.5f,0.5f), lena));
    scene->addObject(new Cylinder(Vector(-6, 3, 3), Vector(90, 30, 0), Vector(0.2f,0.2f,0.2f), red));
    scene->addObject(new Cylinder(Vector(-6, 3.5, 3), Vector(90, 30, 0), Vector(0.2f,0.2f,0.2f), red));

    //scene->addObject(new Plane(Vector(-3, -3, -5),Vector(0,-30,0),white));
    //scene->addObject(new Plane(Vector(-3, -3, -4),Vector(0,60,0),white));

    //directionnal light
    //scene->addLight(new DirectionalLight(Vector(0,1,-1.5),Vector(0,130,70),1, Color(0.1,0.1,0.1), Color(1,1,1), Color(1,1,1)));

    //spotlights
     */
    /*scene->addLight(new PointLight(Vector(2,2,-3.5),Vector(0,130,70),1, Color(0.2,.3,1), Color(0.2,.3,1), Color(1,1,1),0.1,0.3,0.1,2));
    scene->addLight(new PointLight(Vector(-3,1,-2.5),Vector(0,130,70),1, Color(1,.5,.5), Color(1,.5,.5), Color(1,1,1),0.1,0.3,0.1,2));
    scene->addLight(new PointLight(Vector(-1,3,2.5),Vector(0,130,70),1, Color(1,0.95,0.9), Color(1,0.95,0.9), Color(1,1,1),0.05,0.3,0.1,1));
    scene->addLight(new PointLight(Vector(0,-2,-4),Vector(0,130,70),1, Color(1,0.95,0.9), Color(1,0.95,0.9), Color(1,1,1),0.3,0.05,0.2,0.5));*/

    /*Vector camPos(0,0.5,-7);
    Vector rotation(5,0,0);
    scene->camera = new Camera(camPos,rotation,24,5000,5.9);
    scene->camera->setSensorSize(36,24);*/


/*
    int height = 600;
    int width = height / 2.0f * 3.f;

    auto renderImage = std::make_shared<Image>(width,height, Color(1,0,1));

    Raytracer raytracer;
    raytracer.setSampleCount(1);

    std::cout << "\nStarting to render image !\n";
    auto start = std::chrono::high_resolution_clock::now();
    raytracer.render(scene, renderImage,4);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Image finished rendering!\nRender duration : " << elapsed.count() << " s\n";
    //renderImage->convertToLinear();
    //renderImage->revertLinear();
    renderImage->save("render");*/

}