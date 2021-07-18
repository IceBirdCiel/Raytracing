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

Ray Camera::getRay(float x, float y) {
    Vector viewLocalPos((x+1)/2*m_sensorWidth/1000,(y+1)/2*m_sensorHeight/1000, m_focalLength);
    Vector direction = viewLocalPos.normalized();
    Vector focalPoint = direction*m_focalPlaneDist;

    //adding the randomness of the aperture to get the depth of field effect
    //to disable this effect, set the apperture to a high value like 22 or more
    //double a = rand() * 2 * 3.141592654;
    //double r = (m_focalLength/m_aperture)/2 * sqrt(rand());
    double rayOriginX = 0;//r*cos(a);
    double rayOriginY = 0;//r*sin(a);

    Vector rayOrigin(rayOriginX, rayOriginY, 0);
    Vector finalDirection = (focalPoint - rayOrigin).normalized();

    return localToGlobal(Ray(Point(rayOriginX,rayOriginY, 0), finalDirection));

}
