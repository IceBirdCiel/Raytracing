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

void Setup::setupRenderer() {
    std::cout << " ---- CPU RAYTRACER ---- \n\n";
    std::vector<std::string> sceneNames = std::vector<std::string>();
    findSceneFiles(sceneNames);
    int sceneId = chooseAScene(sceneNames);
    auto scene = FileLoader::loadScene("resources/serialized/" + sceneNames[sceneId]);
    if(scene != nullptr){
        std::cout << "Scene " << sceneId << " loaded !\n\n";
    }else{
        std::cerr << "Error while loading sceneNames[sceneId].\n";
    }

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

    std::cout << "Choose a scene to render : \n";

    for (int i = 0; i < sceneNames.size(); ++i) {
        std::cout << i << " - " << sceneNames[i] << "\n";
    }
    std::string sceneId;
    std::cin >> sceneId;
    //checks if sceneId is a number
    if(!sceneId.empty() && std::find_if(sceneId.begin(), sceneId.end(), [](unsigned char c) { return !std::isdigit(c); }) == sceneId.end()){
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
