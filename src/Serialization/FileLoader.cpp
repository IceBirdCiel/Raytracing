#include <iostream>
#include <fstream>
#include <map>
#include "FileLoader.h"
#include "../Objects/Plane.h"
#include "../Objects/Lights/PointLight.h"

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
            auto material = new Material((Color) matData["ambient"], (Color) matData["diffuse"],
                     (Color) matData["specular"], (float) matData["shininess"]);
            _materials[matData["name"]] = material;

            auto matTexId = matData.find("texture");
            if(matTexId != matData.end()){
                material->texture = _textures[matTexId.value()];
            }
        }
        json objectsData = data["objects"];
        for(json& objData : objectsData){
            std::string type = objData["type"];
            Vector position(objData["position"]);
            Vector rotation(objData["rotation"]);
            Vector scale(objData["scale"]);

            Material* objMat = nullptr;
            auto matId = objData.find("material");
            if(matId != objData.end()){
                objMat = _materials[matId.value()];
            }
            if(type == "plane"){
                scene->addObject(new Plane(position, rotation, scale, *objMat));
            } else if(type == "square") {

            } else if(type == "sphere") {

            } else if(type == "cube") {

            } else if(type == "cylinder") {

            } else if(type == "pointLight"){
                scene->addLight(new PointLight(position, rotation, scale[0], (Color) objData["ambient"],
                           (Color) objData["diffuse"], (Color) objData["specular"], objData["lightConstant"],
                           objData["lightLinear"], objData["lightQuadratic"], objData["intensity"]));
            } else if(type == "camera"){
                scene->camera = new Camera(position, rotation, objData["focalLength"],
                           objData["aperture"], objData["focalPoint"]);
                std::vector<float> sensorSize = objData["sensorSize"];
                scene->camera->setSensorSize(sensorSize[0], sensorSize[1]);
            } else {
                std::cerr << "Unrecognized object type : " << type << std::endl;
            }
        }

        return scene;
    } else {
        std::cerr << "File not found" << std::endl;
        throw std::ios_base::failure("File not found : " + fileName);
    }
}