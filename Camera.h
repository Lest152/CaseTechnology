#include <vector>

using namespace std;

class Camera
{

public:
	Camera(vector<float> p, vector<float> d, float angle_h, float angle_v);
	void setView(vector<float>);					//Метод установки точки обзора и направления камеры
	vector<float> getView();		//Получить точку обзора и направления камеры
	void setFOV_H(float);				//Установка горизонтального угла
	float getFOV_H();		//Вывод горизонтального угла

	void setFOV_V(float);				//Установка вертикального угла
	float getFOV_V();		//Вывод вертикального угла

	void setDirection(vector<float>);
	vector<float> getDirection();


private:
	vector<float> viewPointer;		//Точка обзора
	float fov_h;			//угол горизонтального обзора
	float fov_v;			//угол вертикального обзора
	vector<float> direction;		//Направление обзора камеры
};