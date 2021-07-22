//
// Created by Marine on 13/01/2021.
//

#include "Camera.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera(Vector pos, Vector rot, float focalLength, float aperture, float focalPoint): Entity(pos, rot, Vector(1,1,1)), m_focalLength(focalLength), m_focalPlaneDist(focalPoint), m_aperture(aperture) {

}

void Camera::setSensorSize(float sizeX, float sizeY) {
    m_sensorHeight = sizeY;
    m_sensorWidth = sizeX;
}


void Camera::setupForRay(int samplecount, float random) {
    _sampleCount = samplecount;
    _random = random;
}

Ray Camera::getRay(float x, float y, int sampleIndex) const {

//std::cout << "index " << sampleIndex << std::endl;
    ///x & y appartiennent à [-1,1]
    float viewPosX = x * (m_sensorWidth/2.0f) /1000.0f;
    float viewPosY = y * (m_sensorHeight/2.0f) /1000.0f;
    Vector viewLocalPos(viewPosX,viewPosY, m_focalLength/1000.0f);
    //std::cout << "View local pos " << viewLocalPos << std::endl;
    Vector direction = viewLocalPos.normalized();
    Vector focalPoint = direction*m_focalPlaneDist;


    Vector randomStartPosition = VogelDiskSample(sampleIndex, _sampleCount, _random);
    float radius = (m_focalLength/m_aperture/50)/2;
    //std::cout << "pos " << randomStartPosition << " _random " << _random << " radius " << radius << std::endl;
    //adding the randomness of the aperture to get the depth of field effect
    //to disable this effect, set the apperture to a high value like 22 or more
    /*
    double a = randomDistribution(generator) * 2 * M_PI;
    double r = 1 * sqrt(randomDistribution(generator));
    float rayOriginX = r*cos(a);
    float rayOriginY = r*sin(a);*/

    //std::cout << "a = " << a << ", r = " << r << ", rayOriginX = " << rayOriginX << ", rayOriginY = " << rayOriginY << std::endl;
    float finalX = randomStartPosition[0] * radius;
    float finalY = randomStartPosition[1] * radius;
    Vector rayOrigin(finalX, finalY, 0);
    Vector finalDirection = (focalPoint - rayOrigin).normalized();

    //std::cout << Ray(Point(0,0, 0), direction) << std::endl;
    Ray finalRay = localToGlobal(Ray(Point(finalX,finalY, 0), finalDirection)).normalized();
    //std::cout << finalRay << std::endl;
    return finalRay;
    return localToGlobal(Ray(Point(0,0, 0), direction));
}

Vector Camera::VogelDiskSample(int sampleIndex, int samples, float phi) const {
    //std::cout << phi << std::endl;
    float GoldenAngle = 2.4F;

    float r = sqrt(sampleIndex + 0.5F) / sqrt(samples);
    float theta = sampleIndex * GoldenAngle + phi*100;

    float sine = sin(theta);
    float cosine = cos(theta);

    return Vector(r * cosine, r * sine,0);
}

float Camera::InterleavedGradientNoise(Vector pos) const {
    Vector magic = Vector(0.06711056, 0.00583715, 52.9829189);
    double integralPart = 0;
    return modf(magic[0] * modf(pos.dot(Vector(magic[0],magic[1],magic[2])), &integralPart), &integralPart);
}
