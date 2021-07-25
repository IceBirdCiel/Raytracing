//
// Created by Antoine on 25/07/2021.
//
#pragma once
#include <string>
#include <vector>


class Setup {
public:
    static void setupRenderer();
private:
    static void findSceneFiles(std::vector<std::string>& sceneNames);
    static int chooseAScene(std::vector<std::string>& sceneNames);
};