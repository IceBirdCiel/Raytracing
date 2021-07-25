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
#include "Serialization/FileLoader.h"
#include <algorithm>
#include <chrono>
#include <memory>


int main(int argc, char** argv) {
    //                   THE REAL SHIT

    auto scene = FileLoader::loadScene("resources/serialized/Scene1.scene");
    //SkySphere * skybox = new SkySphere("phalzer_forest_01.png");
    //scene->setSkybox(skybox);

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
    renderImage->save("render");

}