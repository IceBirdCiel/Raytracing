#pragma once
#include "Vector.h"
#include "Matrix.h"

class Camera {
public:
	void setPosition(Vector position);
	void setTarget(Vector target);
	virtual void update();
	Matrix getView();
	Matrix getProjection();
	Vector getPosition();
	float FOV{};
	float speed{};
	float yaw{};
	float pitch{};
private:
	void setProjectionMatrix(float FOV, float near, float far);
	void LookAt();
	Vector _position;
	Vector _target;
	Vector _forward;
	Vector _right;
	Vector _up;
	Matrix _view{};
	Matrix _projection{};
};
