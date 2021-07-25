//
// Created by Antoine on 25/07/2021.
//
#pragma once
#include <string>
#include <vector>
#include "Scene/Scene.h"


class Setup {
public:
    bool setupRenderer();
    std::shared_ptr<Scene> scene;
    int renderWidth;
    int renderHeight;
    bool enableShadows;
    float aperture;
    int sampleCount;
    int SSAA;
    std::string outputName;

private:
    static void findSceneFiles(std::vector<std::string>& sceneNames);
    static int chooseAScene(std::vector<std::string>& sceneNames);
    static bool isNumber(std::string string);

    void chooseRenderSettings();


    void chooseSensorSize();

    int chooseSensorWidth();

    int chooseSensorHeight();

    void chooseRenderSize();

    void chooseEnableShadows();

    void chooseEnableDOF();

    void chooseEnableSSAA();

    void chooseAperture();

    void chooseSampleCount();

    void chooseRenderOutputName();
    int sensorWidth;
    int sensorHeight;
};