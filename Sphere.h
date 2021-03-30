#include "Figure.h"


class Sphere : public Figure
{
private:
	double radius = 0.0;

public:
	void setRadius(double);
	double getRadius();
};