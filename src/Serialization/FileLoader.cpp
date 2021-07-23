#include "FileLoader.h"

Scene FileLoader::loadScene(const std::string &fileName) {
    std::ifstream file(fileName);
    std::string line;
    std::string fileContent;
    if(file.is_open()){
        while(std::getline(file, line)){
            fileContent += line;
        }
        file.close();

        json data = json::parse(fileContent);

        Scene scene;


        return scene;
    } else {
        throw std::ios_base::failure("File not found : " + fileName);
    }
}
