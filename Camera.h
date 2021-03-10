#include <vector>

class Camera()
{
	public:
	virtual void setView() = 0;					//Метод установки точки обзора и направления камеры
	virtual vector<float> getView() = 0;		//Получить точку обзора и направления камеры
	
	virtual void setFOV_H() = 0;				//Установка горизонтального угла
	virtual vector<float> getFOV_H() = 0;		//Вывод горизонтального угла
	
	virtual void setFOV_V() = 0;				//Установка вертикального угла
	virtual vector<float> getFOV_V() = 0;		//Вывод вертикального угла
	
	private:
	vector<float> viewPointer;		//Точка обзора
	vector<float> fov_h;			//угол горизонтального обзора
	vector<float> fov_v;			//угол вертикального обзора
	vector<float> direction;		//Направление обзора камеры
};