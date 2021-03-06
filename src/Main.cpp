
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Image.h"
#include "Rendering/Raytracer.h"
#include <chrono>
#include "Setup.h"

int main(int argc, char** argv) {
    Setup setup;
    bool setupDone = setup.setupRenderer();
    if(setupDone){
        Material bg(Color(1, 1, 1), Color(1, 1, 1), Color(1, 1, 1), 0);
        bg.texture = new Image("spacePanoramic.png");
        setup.scene->setSkybox(new SkySphere(10000, bg, *setup.scene->camera));
        auto renderImage = std::make_shared<Image>(setup.renderWidth,setup.renderHeight, Color(1,0,1));
        Raytracer raytracer;
        std::cout << "\nStarting to render image !\n";
        auto start = std::chrono::high_resolution_clock::now();
        raytracer.render(setup.scene, renderImage,setup.SSAA, setup.enableShadows);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Image finished rendering!\nRender duration : " << elapsed.count() << " s\n";
        //renderImage->toLinear();
        //renderImage->tosRGB();
        renderImage->save(setup.outputName);
    }else{
        std::cout << "Aie, coup dur pour Guillaume..." << std::endl;
    }
    return 0;
}