#include "Sphere.h"


void Sphere::setRadius(double r)
{
	radius = r;
}

double Sphere::getRadius()
{
	return radius;
}

vector<float> Sphere::getPoint()
{
	return startPoint;
}

void Sphere::setColor(int r, int g, int b)
{
	R = r;
	G = g;
	B = b;
}

vector<int> Sphere::getColor()
{
	return 0;
}

void Sphere::setPoint(vector<float> center)
{
	startPoint = center;
}

vector<float> Sphere::interPoints(vector<float> viewer, vector<float> direction)
{
	vector<float> delta = startPoint - viewer;

	float a = direction * direction;
	float half_b = direction * delta * (-1.0f);
	float c = delta * delta - radius * radius;

	vector<float> result;
	float discr = half_b * half_b - a * c;

	if (discr < -epsilon)
		return result;
	else if (discr > epsilon)
	{
		float root1 = (half_b - sqrt(discr)) / a;

		result.push_back(viewer - direction * root1);

		return result;
	}
	else
	{
		float root0 = half_b / a;

		result.push_back(viewer - direction * root0);
		return result;
	}
}