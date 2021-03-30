#include <vector>

class ICamera
{
	public:
	virtual void setView() = 0;					//Метод установки точки обзора и направления камеры
	virtual vector<float> getView() = 0;		//Получить точку обзора и направления камеры
	
	virtual void setFOV_H() = 0;				//Установка горизонтального угла
	virtual vector<float> getFOV_H() = 0;		//Вывод горизонтального угла
	
	virtual void setFOV_V() = 0;				//Установка вертикального угла
	virtual vector<float> getFOV_V() = 0;		//Вывод вертикального угла
	
	virtual void setDirection() = 0;
	virtual vector<float> getDirection() = 0;
	
};