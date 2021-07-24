#include <iostream>
#include <fstream>
#include <map>
#include "FileLoader.h"

std::shared_ptr<Scene> FileLoader::loadScene(const std::string &fileName) {
    std::ifstream file;
    std::string line;
    std::string fileContent;
    file.open(fileName);
    if(file.is_open()){
        while(std::getline(file, line)){
            fileContent += line;
        }
        file.close();

        json data = json::parse(fileContent);

        std::map<std::string, Image*> _textures;
        std::map<std::string, Material*> _materials;
        auto scene = std::make_shared<Scene>();
        scene->setBackground(Color(data["background"]["color"][0],data["background"]["color"][1], data["background"]["color"][2]));

        json texturesData = data["textures"];
        for(json& textureData : texturesData) {
            std::string texFileName = textureData["src"];
            auto texture = new Image(texFileName);
            _textures[textureData["id"]] = texture;
        }
        json materialsData = data["materials"];
        for(json& matData : materialsData){
            auto material = new Material(matData["ambient"], matData["diffuse"], matData["specular"], matData["shininess"]);
            _materials[matData["name"]] = material;

            auto matTexId = matData.find("texture");
            if(matTexId != matData.end()){
                material->texture = _textures[matTexId.value()];
            }
        }

        return scene;
    } else {
        std::cerr << "File not found" << std::endl;
        throw std::ios_base::failure("File not found : " + fileName);
    }
}