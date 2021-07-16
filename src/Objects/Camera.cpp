//
// Created by Marine on 13/01/2021.
//

#include "Camera.h"
#include <iostream>


void Camera::update() {
    //speed = 2.5f * Engine::instance->deltaTime;
    _forward = (_position - _target).normalized();

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    Vector direction(0,0,0);
    direction[0] = cos((3.141592654 * yaw) / 180.0) * cos((3.141592654 * pitch) / 180.0);
    direction[1] = sin((3.141592654 * pitch) / 180.0);
    direction[2] = sin((3.141592654 * yaw) / 180.0) * cos((3.141592654 * pitch) / 180.0);
    _forward = direction.normalized();

    Vector up(0.0f, 1.0f, 0.0f);
    _right = (up.cross(_forward)).normalized();
    _up = _forward.cross(_right);

    float viewportWidth = 100;
    float viewportHeight = 100;
    float ratio = (float) viewportWidth / (float)viewportHeight;

    setProjectionMatrix(FOV, 0.01f, 100.0f);
    LookAt();
}

void Camera::setPosition(Vector position) {
    _position = position;
}

void Camera::setTarget(Vector target) {
    _target = target;
}

Matrix Camera::getView() {
    return _view;
}
Matrix Camera::getProjection() {
    return _projection;
}

Vector Camera::getPosition() {
    return _position;
}

void Camera::setProjectionMatrix(float FOV, float near, float far)
{
    // set the basic projection matrix
    float scale = 1 / tan(FOV * 0.5 * 3.141592654 / 180);
    _projection(0, 0) = scale; // scale the x coordinates of the projected point
    _projection(1, 1) = scale; // scale the y coordinates of the projected point
    _projection(2, 2) = -far / (far - near); // used to remap z to [0,1]
    _projection(3, 2) = -far * near / (far - near); // used to remap z [0,1]
    _projection(2, 3) = -1; // set w = -z
    _projection(3, 3) = 0;
}
// C++ code
// this code assumes the camera is initially looking towards (1,0,0) positive z direction
// if you want the initial direction to be along the x or y coordinates then try swapping
// the order when setting the components
// dir = target direction
// up = a vector which is perpendicular to the camera axis
void Camera::LookAt() {
    Vector z((_position + _forward).normalized());
    z.norm();
    Vector x = _up.cross(z); // x = up cross z
    x.norm();
    Vector y = z.cross(x); // y = z cross x
    Matrix m;
    m(0, 0) = x[0];
    m(0, 1) = x[1];
    m(0, 2) = x[2];

    m(1, 0) = y[0];
    m(1, 1) = y[1];
    m(1, 2) = y[2];

    m(2, 0) = z[0];
    m(2, 1) = z[1];
    m(2, 2) = z[2];

    m(3, 0) = _position[0];
    m(3, 1) = _position[1];
    m(3, 2) = _position[2];
    _view = m;
}