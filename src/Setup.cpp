//
// Created by Antoine on 25/07/2021.
//

#include "Setup.h"
#include "Serialization/FileLoader.h"
#include <memory>
#include <string>
#include <filesystem>
#include <iostream>
#include <windows.h>

bool Setup::setupRenderer() {
    std::cout << " ---- CPU RAYTRACER ---- \n\n";
    std::vector<std::string> sceneNames = std::vector<std::string>();
    findSceneFiles(sceneNames);
    int sceneId = chooseAScene(sceneNames);
    auto scn = FileLoader::loadScene("resources/serialized/" + sceneNames[sceneId]);
    if(scn != nullptr){
        scene = scn;
        std::cout << "'" << sceneNames[sceneId] << "' loaded !\n\n";
        chooseRenderSettings();
        chooseRenderOutputName();
        std::cout << "\n\nRender settings ready !\n";
        return true;
    }else{
        std::cerr << "Error while loading " << sceneNames[sceneId] << ".\n";
        return false;
    }

}

void Setup::chooseRenderSettings() {
    chooseSensorSize();
    chooseRenderSize();
    chooseEnableShadows();
    chooseEnableDOF();
    chooseEnableSSAA();
}

void Setup::findSceneFiles(std::vector<std::string>& sceneNames) {

    std::string directory = "resources/serialized/";
    for (const auto & entry : std::filesystem::directory_iterator(directory)){
        std::string path = entry.path().string();
        size_t pos = std::string::npos;
        while ((pos  = path.find(directory) )!= std::string::npos)
        {
            // If found then erase it from string
            path.erase(pos, directory.length());
        }
        sceneNames.emplace_back(path);
    }
}

int Setup::chooseAScene(std::vector<std::string>& sceneNames) {

    std::cout << "\nChoose a scene to render : \n";

    for (int i = 0; i < sceneNames.size(); ++i) {
        std::cout << i << " - " << sceneNames[i] << "\n";
    }
    std::string sceneId;
    std::cin >> sceneId;
    //checks if sceneId is a number
    if(isNumber(sceneId)){
        int id = std::stoi(sceneId);
        if(id < 0 || id >= sceneNames.size()){
            std::cerr << "Please select a number among those listed above.\n\n";
            Sleep(1000);

            return chooseAScene(sceneNames);
        }else{
            return id;
        }
    }else{
        std::cerr << "Please select a number among those listed above.\n\n";
        Sleep(1000);
        return chooseAScene(sceneNames);
    }
}

bool Setup::isNumber(std::string string) {
    return !string.empty() && std::find_if(string.begin(), string.end(), [](unsigned char c) { return !std::isdigit(c); }) == string.end();
}

void Setup::chooseSensorSize() {
    std::cout << "\nSetting the sensor size (type 'default' for default value)\n";
    float tempWidth = chooseSensorWidth();
    if(tempWidth < 0){
        std::cout << "Sensor size set to default : 36x24mm 'fullframe'\n";
        sensorWidth = 36;
        sensorHeight = 24;
        scene->camera->setSensorSize(sensorWidth,sensorHeight);
        return;
    }
    sensorWidth = tempWidth;
    sensorHeight = chooseSensorHeight();
    scene->camera->setSensorSize(sensorWidth,sensorHeight);
    std::cout << "Sensor size set to : " << sensorWidth << "x" << sensorHeight << "mm\n";

}

int Setup::chooseSensorWidth() {
    std::cout << "\nPlease enter the desired width :\n";
    std::string sensorW;
    std::cin >> sensorW;
    if(sensorW == "default"){
        return -1;
    }else{
        if(isNumber(sensorW)){
            int sensorWint = std::stoi(sensorW);
            if(sensorWint < 0){
                std::cerr << "You cannot set a negative width.\n\n";
                Sleep(1000);
                return chooseSensorWidth();
            }
            return sensorWint;
        }else{
            std::cerr << "Please enter a number (in mm).\n\n";
            Sleep(1000);
            return chooseSensorWidth();
        }
    }
}

int Setup::chooseSensorHeight() {
    std::cout << "\nPlease enter the desired height :\n";
    std::string sensorH;
    std::cin >> sensorH;
    if(sensorH.size() == 0){
        std::cerr << "A custom width has been set.\nPlease enter a number (in mm).\n\n";
        Sleep(1000);
        return chooseSensorHeight();
    }else{
        if(isNumber(sensorH)){
            int sensorHint = std::stoi(sensorH);
            if(sensorHint < 0){
                std::cerr << "You cannot set a negative height.\n\n";
                Sleep(1000);
                return chooseSensorHeight();
            }
            return sensorHint;
        }else{
            std::cerr << "Please enter a number (in mm).\n\n";
            Sleep(1000);
            return chooseSensorHeight();
        }
    }
}

void Setup::chooseRenderSize() {
    std::cout << "\nPlease enter the height of your image (the width will be set according to the dimensions of the sensor) :\n";
    std::string renderH;
    std::cin >> renderH;

    if(isNumber(renderH)){
        int renderHint = std::stoi(renderH);
        if(renderHint < 0){
            std::cerr << "You cannot set a negative height.\n\n";
            Sleep(1000);
            return chooseRenderSize();
        }
        renderHeight = renderHint;
        //std::cout << renderHint <<  " * " << sensorWidth << " / " << sensorHeight;
        renderWidth = ((float)(renderHint)*sensorWidth)/(float)sensorHeight;
        std::cout << " = " << renderWidth << std::endl;
    }else{
        std::cerr << "Please enter a number (in pixels).\n\n";
        Sleep(1000);
        return chooseRenderSize();
    }
    std::cout << "Render size will be " << renderWidth << "x" << renderHeight << "px\n";
}

void Setup::chooseEnableShadows() {
    std::cout << "\nEnable shadow casting ? [Y/N] \n";
    std::string shadows;
    std::cin >> shadows;
    if(shadows == "Y" || shadows == "y"){
        enableShadows = true;
    }else if(shadows == "N" || shadows == "n"){
        enableShadows = false;
    }else{
        std::cerr << "Please enter Y to enable shadows or N to disable shadows.\n";
        Sleep(1000);
        return chooseEnableShadows();
    }
}

void Setup::chooseEnableDOF() {
    std::cout << "\nEnable DOF ? [Y/N] \n";
    std::string enableDOF;
    std::cin >> enableDOF;
    if(enableDOF == "Y" || enableDOF == "y"){
        chooseAperture();
        chooseSampleCount();
    }else if(enableDOF == "N" || enableDOF == "n"){
        scene->camera->setAperture(1000000);
        scene->camera->setSampleCount(1);
        return;
    }else {
        std::cerr << "Please enter Y to enable depth of field or N to disable depth of field.\n";
        Sleep(1000);
        return chooseEnableDOF();
    }
}

void Setup::chooseAperture() {
    std::cout << "\nChoose aperture :\n";
    float apt;
    std::cin >> apt;
    if (apt <= 0) {
        std::cerr << "Please choose an aperture greater than 0.\n";
        Sleep(1000);
        return chooseAperture();
    }
    scene->camera->setAperture(apt);
}

void Setup::chooseSampleCount() {
    std::cout << "\nChoose samples per pixel :\n";
    int sCount;
    std::cin >> sCount;
    if (sCount <= 0) {
        std::cerr << "Please choose sample count greater than 0.\n";
        Sleep(1000);
        return chooseSampleCount();
    }
    scene->camera->setSampleCount(sCount);
}


void Setup::chooseEnableSSAA() {
    std::cout << "\nChoose super-sampling anti-aliasing level : (1, 2, 4...)\n";
    int ssaaCount;
    std::cin >> ssaaCount;
    if (ssaaCount <= 0) {
        std::cerr << "Please choose SSAA value greater than 0.\n";
        Sleep(1000);
        return chooseEnableSSAA();
    }
    SSAA = ssaaCount;
}

void Setup::chooseRenderOutputName() {
    std::cout << "\nChoose the output file name :\n";
    std::string name;
    std::cin >> name;
    outputName = name;
}
