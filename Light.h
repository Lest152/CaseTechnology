class Light
{
	public:
	
	virtual void setIntence() = 0;		//Установка интенсивности света
	virtual int getIntence() = 0;		//Получение интенсивности света
	
	virtual void setDirection() = 0;	//Установка направления света
	virtual vector<float> getDirection() = 0;	//Получение направления света
	
	virtual void setPoint() = 0;		//Установка точки начала координат источника света
	virtual vector<float> getPoint() = 0;		//Получение точки начала координат источника света
	
	private:
	int intence;			//Интенсивность света
	vector<float> direction;		//Направление источника света
	vector<float> point;			//Точка начала источника света
};