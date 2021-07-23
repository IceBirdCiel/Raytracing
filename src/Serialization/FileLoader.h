#pragma once

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "../Scene/Scene.h"

using namespace nlohmann;

class FileLoader {
public:
    static Scene loadScene(const std::string& fileName);
    //static json saveScene(const std::string& fileName, const json& data);
};


