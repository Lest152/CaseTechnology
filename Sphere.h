#include "Figure.h"


class Sphere : public Figure
{
private:
	double radius = 0.0;
	vector<float> startPoint;
	int R, G, B;

public:
	void setRadius(double);
	double getRadius();
	vector<float> getPoint();
	void setColor(int r, int g, int b);
	vector<int> getColor();
	void setPoint(vector<float> center);
	vector<float> interPoints(vector<float> viewer, vector<float> direction);
};