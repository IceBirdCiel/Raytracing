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
#include "Objects/Lights/SpotLight.h"
#include "Rendering/SkySphere.h"
#include <algorithm>

int main(int argc, char** argv) {

    std::cout << "Hello World !" << std::endl;

    //                   THE REAL SHIT

    Scene scene;
    scene.setBackground(Color(0.2, 0.2, 1));
    //SkySphere * skybox = new SkySphere("phalzer_forest_01.png");
    //scene.setSkybox(skybox);

    Color specular(0.75,0.75,0.75);

    Material red(Color(1,0, 0),Color(1,0, 0),specular,50);
    red.texture = new Image("Nicolas.jpg");
    Material yellow(Color(1,1, 0),Color(1,1, 0),specular,50);
    Material orange(Color(1,0.5, 0),Color(1,0.5, 0),specular,50);
    Material green(Color(0,1, 0),Color(0,1, 0),specular,50);;
    Material cyan(Color(0,1, 1),Color(0,1, 1),specular,50);
    Material blue(Color(0,0, 1),Color(0,0, 1),specular,50);
    blue.texture = new Image("Nico.jpg");
    Material magenta(Color(1,0, 1),Color(1,0, 1),specular,50);
    magenta.texture = new Image("lena.png");
    Material black(Color(0,0, 0),Color(0,0, 0),specular,5);
    Material white(Color(1, 1, 1), Color(1, 1, 1), specular, 50);
    Material lena(Color(1, 1, 1), Color(1, 1, 1), specular, 50);
    lena.texture = new Image("lena.png");
    Material grey(Color(0.7, 0.6, 0.7), Color(0.385, 0.385, 0.4), specular, 50);
    Material donoro(Color(0.7, 0.6, 0.7), Color(0.6,0, 0.6), specular, 50);
    donoro.texture = new Image("donoro.jpg");

    //walls
    //sol
    scene.addObject(new Plane(Vector(0, -3, 5), Vector(90,0,0), grey));
    //mur arriere
    scene.addObject(new Plane(Vector(0, -3, 5), Vector(0,30,0), grey));
    scene.addObject(new Plane(Vector(-5, -3, 5), Vector(0,-60,0), grey));

    //scene.addObject(new Sphere(Vector(0, 0, 0), Vector(0,90,90), Vector(1.5,1.5,1.5), lena));
    scene.addObject( new Sphere(Vector(2, -1, -3),Vector(0,90,90),Vector(1,1,1),blue));
    scene.addObject(new Cube(Vector(-5, -2, 3), Vector(0,30,0), Vector(1.f,1.f,1.5f), orange));
    
    scene.addObject(new Cube(Vector(-3, 1, 0), Vector(0, 0, 45), Vector(1.f, 1.f, 1.f), donoro));
    
    scene.addObject(new Sphere(Vector(1, 2.0, -2.5), Vector(), Vector(1,1,1), orange));
    scene.addObject(new Sphere(Vector(-2, -1.2, -2), Vector(0,90,90), Vector(0.75,0.75,0.75), red));
    scene.addObject(new Sphere(Vector(-1.7, 1.0, 0),Vector(),Vector(0.65f,0.65f,0.65f),magenta));
    scene.addObject(new Sphere(Vector(-0.5, -1.0, -0.7),Vector(),Vector(0.65f,0.65f,0.65f),green));
    scene.addObject(new Sphere(Vector(0.5, -0.5, -2.5),Vector(),Vector(0.25f,0.25f,0.25f),yellow));

    scene.addObject(new Square(Vector(2, 0, -3), Vector(90, 0, 0),Vector(1.f,1.f,1.f), magenta));
    //pillars
    scene.addObject(new Cylinder(Vector(3, 0, 0), Vector(0, 0, 0), Vector(0.5f,0.5f,0.5f), white));
    scene.addObject(new Cylinder(Vector(1.5, 0, 3), Vector(0, 0, 0), Vector(0.5f,0.5f,0.5f), white));
    scene.addObject(new Cylinder(Vector(-2, 0, 4.5), Vector(0, 0, 0), Vector(0.5f,0.5f,0.5f), white));
    scene.addObject(new Cylinder(Vector(-5, 4, 3), Vector(90, 30, 0), Vector(0.5f,0.5f,0.5f), red));

    //scene.addObject(new Plane(Vector(-3, -3, -5),Vector(0,-30,0),white));
    //scene.addObject(new Plane(Vector(-3, -3, -4),Vector(0,60,0),white));

    scene.addLight(new DirectionalLight(Vector(0,0,-8),Vector(0,130,70),1, Color(0.0,0.0,0.0), Color(1,1,1), Color(1,1,1)));

    Vector camPos(0,0.5,-7);
    Vector rotation(5,0,0);
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