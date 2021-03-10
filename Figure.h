#include <vector>

class Figure
{
	public:
		
		virtual getPoints() = 0;						//Метод получения точки начала координаты фигуры
		virtual vector<float> interPoints() = 0;		//Метод расчета точек пересечения
		virtual setColor() = 0;							//Метод задания цвета
		
	private:
	
		vector<float> startPoint;	//Точка центра фигуры
		int R,G,B;					//Цвет
};