#include "Camera.h"
#include <vector>

using namespace std;

Camera::Camera(vector<float> p, vector<float> d, float angle_h, float angle_v)
{
	viewPointer = p;
	direction = d;
	fov_v = angle_v;
	fov_h = angle_h;
}

void Camera::setView(vector<float> p)
{
	viewPointer = p;
}

vector<float> Camera::getView()
{
	return viewPointer;
}

void Camera::setFOV_H(float angle_h)
{
	fov_h = angle_h;
}

float Camera::getFOV_H()
{
	return fov_h;
}

void Camera::setFOV_V(float angle_v)
{
	fov_v = angle_v;
}

float Camera::getFOV_V()
{
	return fov_v;
}

void Camera::setDirection(vector<float> d)
{
	direction = d;
}

vector<float> Camera::getDirection()
{
	return direction;
}

	
