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
	vector<int> color;
	return color;
}

void Sphere::setPoint(vector<float> center)
{
	startPoint = center;
}
/*
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

		float a;
		result.push_back(a);
		result.push_back(viewer - direction * root1);

		return result;
	}
	else
	{
		float root0 = half_b / a;

		result.push_back(viewer - direction * root0);
		return result;
	}
}*/

inline float operator*(vector<float> p0, vector<float> p1)
{
	float result = 0;
	for (int i = 0; i < p0.size(); i++)
		result += p0[i] * p1[i];
	return result;
}

inline vector<float> operator*(vector<float> p0, float t)
{
	for (int i = 0; i < p0.size(); i++)
		p0[i] *= t;
	return p0;
}

inline vector<float> operator-(vector<float> p0, vector<float> p1)
{
	for (int i = 0; i < p0.size(); i++)
		p0[i] -= p1[i];
	return p0;
}