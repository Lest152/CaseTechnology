#include <vector>

using namespace std;

class Camera
{

public:
	Camera(vector<float> p, vector<float> d, float angle_h, float angle_v);
	void setView(vector<float>);					//����� ��������� ����� ������ � ����������� ������
	vector<float> getView();		//�������� ����� ������ � ����������� ������
	void setFOV_H(float);				//��������� ��������������� ����
	float getFOV_H();		//����� ��������������� ����

	void setFOV_V(float);				//��������� ������������� ����
	float getFOV_V();		//����� ������������� ����

	void setDirection(vector<float>);
	vector<float> getDirection();


private:
	vector<float> viewPointer;		//����� ������
	float fov_h;			//���� ��������������� ������
	float fov_v;			//���� ������������� ������
	vector<float> direction;		//����������� ������ ������
};