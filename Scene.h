#include <Figure.h>
#include <Camera.h>

class Scene()
{
	private:
	vector<Figure> figures;			//Фигуры на сцене
	Camera camera;					//Расположение камеры на сцене
	vector<Light> light;			//Объект свет на сцене
};