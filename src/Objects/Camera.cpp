//
// Created by Marine on 13/01/2021.
//

#include "Camera.h"
#include <iostream>
#include "../Math/Ray.h"

Camera::Camera(Vector pos, Vector rot, float focalLength, float aperture, float focalPoint): Entity(pos, rot, Vector(1,1,1)), m_focalLength(focalLength), m_focalPlaneDist(focalPoint), m_aperture(aperture) {

}

void Camera::setSensorSize(float sizeX, float sizeY) {
    m_sensorHeight = sizeY;
    m_sensorWidth = sizeX;
}

Ray Camera::getRay(float x, float y) const {


    ///x & y appartiennent à [-1,1]
    float viewPosX = x * (m_sensorWidth/2.0f) /1000.0f;
    float viewPosY = y * (m_sensorHeight/2.0f) /1000.0f;
    Vector viewLocalPos(viewPosX,viewPosY, m_focalLength/1000.0f);
    //std::cout << "View local pos " << viewLocalPos << std::endl;
    Vector direction = viewLocalPos.normalized();
    Vector focalPoint = direction*m_focalPlaneDist;

    //adding the randomness of the aperture to get the depth of field effect
    //to disable this effect, set the apperture to a high value like 22 or more
    double a = rand() * 2 * 3.141592654;
    double r = (m_focalLength/m_aperture/1000)/2 * sqrt(rand());
    double rayOriginX = r*cos(a);
    double rayOriginY = r*sin(a);

    Vector rayOrigin(rayOriginX, rayOriginY, 0);
    Vector finalDirection = (focalPoint - rayOrigin).normalized();

    //std::cout << Ray(Point(0,0, 0), direction) << std::endl;

    return localToGlobal(Ray(Point(rayOriginX,rayOriginY, 0), finalDirection));
    //return localToGlobal(Ray(Point(0,0, 0), direction));
}
