#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <gl\glut.h>	//Подключение библиотеки glut.h (openGL)

using namespace std;

static const float epsilon = 1e-4f; //задание точности
static const float PI = 3.14159265;
float xc0, yc0, r;	//центр окружности + радиус

struct Coord
{
	float x;
	float y;
};

vector<Coord> points = {};



inline float operator*(Coord p0, Coord p1)
{
	return p0.x*p1.x + p0.y*p1.y;
}

inline Coord operator*(Coord p0, float t)
{
	p0.x *= t;
	p0.y *= t;
	return p0;
}

inline Coord operator-(Coord p0, Coord p1)
{
	p0.x -= p1.x;
	p0.y -= p1.y;
	return p0;
}

vector<Coord> findInterPoint(Coord start_point, Coord direction, Coord center, float radius)
{
	Coord delta = center - start_point;

	float a = direction*direction;
	float half_b = direction*delta*(-1.0f);
	float c = delta*delta - radius*radius;

	vector<Coord> result;
	float discr = half_b*half_b - a*c;

	if (discr < -epsilon)
		return result;
	else if (discr > epsilon)
	{
		float root0 = (half_b + sqrt(discr)) / a;
		float root1 = (half_b - sqrt(discr)) / a;

		result.push_back(start_point - direction*root0);
		result.push_back(start_point - direction*root1);

		return result;
	}
	else
	{
		float root0 = half_b / a;

		result.push_back(start_point - direction*root0);
		return result;
	}
}

double double_rand(double r_max)
{
	if (r_max != 0)
	{
		int rand_max = r_max * 100;
		int r = rand() % rand_max;
		double t = (double)r / 100;

		return t;
	}
	else
		return 0;
}

double ran_sign(double k, double dk)
{
	int sign = rand() % 2;

	if (sign == 0)
		k = k + dk;
	else
		k = k - dk;

	return k;
}

//OPENGL 


//функция отрисовки круга
void drawCircle(float x, float y, float r)
{
	const int amountSegments = 30;
	glPointSize(1);
	glBegin(GL_LINE_LOOP);
	glColor3d(1, 1, 0);
	for (int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);
		float dx = r * cosf(angle);
		float dy = r * sinf(angle);
		glVertex2f(x + dx, y + dy);
	}

	glEnd();
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);


	//----------Отрисовка оси координат--------
	glBegin(GL_LINES);
	glColor3d(1, 1, 1);
	glVertex2f(-25, 0);
	glVertex2f(25, 0);

	glVertex2f(0, 25);
	glVertex2f(0, -25);
	glEnd();
	//---------------------------------------

	//----------Отрисовка точек пересечения луча и окружности--------
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3d(0, 0, 1);
	for (int i = 0; i < points.size(); i++)
		glVertex2f(points[i].x, points[i].y);

	glEnd();
	//---------------------------------------

	drawCircle(xc0, yc0, r);

	glFlush();
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "russian");

	float x0, y0, x1, y1;	//координаты стартовой прямой
	
	int alfa;			//угол альфа

	cout << "Введите координаты прямой (диапазон оси координат [-25;25]): ";
	cin >> x0 >> y0 >> x1 >> y1;

	cout << "Введите координаты центра окружности: ";
	cin >> xc0 >> yc0;

	cout << "Введите радиус окружности: ";
	cin >> r;

	const Coord start_point{ x0, y0 };	//Задаем начальную точку луча

	const Coord center{ xc0, yc0 };
	const float radius = r;

	cout << "Введите градус угла рассеивания лучей: ";
	cin >> alfa;

	//вычисление максимальных приращений dx и dy в заданном секторе
	double dx, dy;

	double s = sqrt(pow((x1 - x0), 2) + pow((y1 - y0), 2));
	double beta = atan(fabs(y1 - y0) / (fabs(x1 - x0)));
	double p = s*tan(alfa / 2 * PI / 180);

	dx = p * sin(beta);

	if (beta * 180 / PI != 90)
		dy = p * cos(beta);
	else
		dy = 0;

	int count;
	cout << "Введите количество желаемых лучей из начальной точки в заданном секторе: ";
	cin >> count;

	cout << endl;

	vector<Coord> linesDirection;

	Coord start_direction{ x1 - x0, y1 - y0 };
	linesDirection.push_back(start_direction);

	for (int i = 0; i < count; i++)
	{
		double x2 = ran_sign(x1, double_rand(dx));
		double y2 = ran_sign(y1, double_rand(dy));
		Coord direction{ (float)x2 - x0, (float)y2 - y0 };

		linesDirection.push_back(direction);
	}

	cout << "Результаты пересечения:" << endl;

	for (int i = 0; i < linesDirection.size(); i++)
	{
		vector<Coord> result = findInterPoint(start_point, linesDirection[i], center, radius);

		switch (result.size())
		{
		case 0:
			cout << "Луч не имеет точек пересечения с заданной окружностью" << endl;
			break;
		case 1:
			cout << "Луч имеет 1 точку пересечения" << endl;
			break;
		case 2: cout << "Луч имеет 2 точки пересечения" << endl;
		}

		for (int i = 0; i < result.size(); i++)
		{
			cout << "   >>> Точка пересечения с координатами: (" << result[i].x << ", " << result[i].y << ")" << endl;
			points.push_back(result[i]);
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);		//Указываем размер окна
	glutInitWindowPosition(100, 100);	//Позиция окна
	glutCreateWindow("OpenGL window");		//Имя окна
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-25, 25, -25, 25);
	glutDisplayFunc(Draw);				//Вызов функции отрисовки
	glutMainLoop();

	system("pause");
	return 0;
}