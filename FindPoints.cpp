#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <gl\glut.h>	//Подключение библиотеки glut.h (openGL)
#include <utility>

#define PI_1   0.01745f
#define PI_180 3.14159f
#define PI_360 6.28318f

using namespace std;

static const float epsilon = 1e-4f; //задание точности
static const float PI = 3.14159265;

int dim; // размерность пространства
vector<float> center; //координаты центра окружности
float radius; //радиус

vector<vector<float>> points = {};

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

vector<vector<float>> findInterPointNEW(vector<float> start_point, vector<float> direction, vector<float> center, float radius)
{
	vector<float> delta = center - start_point;

	float a = direction*direction;
	float half_b = direction*delta*(-1.0f);
	float c = delta*delta - radius*radius;

	vector<vector<float>> result;
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


//Функция умножения матриц
float ** multiplyMatrices(int n, int m, float** a, int z, int w, float** b)
{
	if (m == z)
	{
		float** result = new float*[n];

		for (int i = 0; i < n; i++)
		{
			result[i] = new float[w];
			for (int j = 0; j < w; j++)
			{
				result[i][j] = 0;
				for (int k = 0; k < m; k++)
					result[i][j] += a[i][k] * b[k][j];
			}
		}
		return result;
	}
	return NULL;
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
		glVertex2f(points[i][0], points[i][1]);

	glEnd();
	//---------------------------------------

	drawCircle(center[0], center[1], radius);

	glFlush();
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "russian");

	do
	{
		cout << "Введите желаемую размерность пространства: ";
		cin >> dim;
	} while (dim < 2);


	cout << "Введите координаты прямой: ";
	vector<float> point0, point1; //координаты точек стартовой прямой
								  
	for (int i = 0; i < 2 * dim; i++)
	{
		float v;
		cin >> v;
		if (i < dim)
			point0.push_back(v);
		else
			point1.push_back(v);
	}

	cout << "Введите координаты центра окружности: ";
	for (int i = 0; i < dim; i++)
	{
		float v;
		cin >> v;
		center.push_back(v);
	}

	cout << "Введите радиус окружности: ";
	cin >> radius;

	cout << "Введите градус угла рассеивания лучей: ";
	int alfa;
	cin >> alfa;

	float **rotationMatrixLeft, **rotationMatrixRight; //Матрица поворота
	float **RotationLeft, **RotationRight;

	rotationMatrixLeft = new float *[dim];
	for (int i = 0; i < dim; i++)
		rotationMatrixLeft[i] = new float[dim];

	rotationMatrixRight = new float *[dim];
	for (int i = 0; i < dim; i++)
		rotationMatrixRight[i] = new float[dim];

	RotationLeft = new float *[dim];
	for (int i = 0; i < dim; i++)
		RotationLeft[i] = new float[dim];

	RotationRight = new float *[dim];
	for (int i = 0; i < dim; i++)
		RotationRight[i] = new float[dim];

	//Инициализация единичной матрицы
	for(int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
		{
			if (i != j)
				rotationMatrixLeft[i][j] = rotationMatrixRight[i][j] = 0;
			else
				rotationMatrixLeft[i][j] = rotationMatrixRight[i][j] = 1;
		}

	vector<pair<int, int>> unic_pair;
	
	float **VectorPointRight = new float*[dim];
	for (int i = 0; i < dim; i++)
		VectorPointRight[i] = new float;

	float **VectorPointLeft = new float*[dim];
	for (int i = 0; i < dim; i++)
		VectorPointLeft[i] = new float;

	for (int ind = 0; ind < dim; ind++)
		VectorPointRight[ind][0] = point1[ind];

	for (int ind = 0; ind < dim; ind++)
		VectorPointLeft[ind][0] = point1[ind];

	vector<vector<float>> linesDirection;
	linesDirection.push_back(point1 - point0); //задание центрального луча	

	//Расчет матрицы поворота
	for (int k = 1; k <= alfa/2; k++)
	{
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++)
			{

				for (int k = 0; k < dim; k++)
					for (int c = 0; c < dim; c++)
					{
						if (k != c)
							RotationLeft[k][c] = RotationRight[k][c] = 0;
						else
							RotationLeft[k][c] = RotationRight[k][c] = 1;
					}
				bool contains = false;
				if (i != j)
				{
					for (int k = 0; k < unic_pair.size(); k++)
					{
						if (unic_pair[k].first == i && unic_pair[k].second == j)
						{
							contains = true;
							break;
						}
					}

					if (!contains)
					{
						RotationLeft[i][i] = cos(k * PI / 180);
						RotationLeft[i][j] = -sin(k * PI / 180);
						RotationLeft[j][i] = sin(k * PI / 180);
						RotationLeft[j][j] = cos(k * PI / 180);

						RotationRight[i][i] = cos(k * PI / 180);
						RotationRight[i][j] = sin(k * PI / 180);
						RotationRight[j][i] = -sin(k * PI / 180);
						RotationRight[j][j] = cos(k * PI / 180);

						rotationMatrixLeft = multiplyMatrices(dim, dim, rotationMatrixLeft, dim, dim, RotationLeft);
						rotationMatrixRight = multiplyMatrices(dim, dim, rotationMatrixRight, dim, dim, RotationRight);

						unic_pair.push_back(make_pair(i, j));
						unic_pair.push_back(make_pair(j, i));
					}
				}
			}
		
		// Умножение вектора на матрицу поворота
		VectorPointLeft = multiplyMatrices(dim, dim, rotationMatrixLeft, dim, 1, VectorPointLeft);
		VectorPointRight = multiplyMatrices(dim, dim, rotationMatrixRight, dim, 1, VectorPointRight);
		
		vector<float> point_1, point_2;
		for (int ind = 0; ind < dim; ind++)
		{
			point_1.push_back(VectorPointLeft[ind][0]);
			point_2.push_back(VectorPointRight[ind][0]);
		}
		
		linesDirection.push_back(point_1 - point0);
		linesDirection.push_back(point_2 - point0);		
	}

	cout << "Результаты пересечения:" << endl;

	for (int i = 0; i < linesDirection.size(); i++)
	{
		vector<vector<float>> result = findInterPointNEW(point0, linesDirection[i], center, radius);

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
			vector<float> point;
			cout << "   >>> Точка пересечения с координатами: (";
			for (int j = 0; j < result[i].size(); j++)
			{
				cout << result[i][j] << " ";
				point.push_back(result[i][j]);
			}
			cout << ")" << endl;
			points.push_back(point);
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

	glutDisplayFunc(Draw);			//Вызов функции отрисовки

	glutMainLoop();

	//Освобождение памяти матрицы поворота
	for (int i = 0; i < dim; i++)
		delete[]rotationMatrixLeft[i];

	delete[]rotationMatrixLeft;

	system("pause");
	return 0;
}