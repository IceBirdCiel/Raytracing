#pragma once
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "Entity.h"
#include <random>

class Camera : public Entity {
public:
    Camera(Vector pos, Vector rot, float focalLength, float aperture, float focalPoint);
    void setSensorSize(float sizeX, float sizeY);
    Ray getRay(float x, float y, int sampleIndex) const;
    void setupForRay(int samplecount, float random);

private:
    Vector VogelDiskSample(int sampleIndex, int sampleCount, float phi) const;
    float InterleavedGradientNoise(Vector pos) const;
    float m_focalLength = 24;//the distance between the camera origin and the sensor in millimeters
    float m_aperture = 5.6;//the ratio of the focal length over the diaphragm's diameter
    float m_focalPlaneDist = 10;//the distance between the focal plane and the camera origin in meters

    float m_sensorWidth = 32;//the sensor's width millimeters
    float m_sensorHeight = 24;//the sensor's height in millimeters

    int _sampleCount = 0;
    float _random = 0;

};
