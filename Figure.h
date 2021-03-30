#include <vector>
using namespace std;

static const float epsilon = 1e-4f;

class Figure
{
	public:
		
		virtual vector<float> getPoint() = 0;						//Метод получения точки начала координаты фигуры
		virtual vector<float> interPoints() = 0;		//Метод расчета точек пересечения
		virtual void setColor() = 0;							//Метод задания цвета
		virtual vector<int> getColor() = 0;
		virtual void setPoint() = 0;
		
	private:
	
		vector<float> startPoint;	//Точка центра фигуры
		int R,G,B;					//Цвет
};