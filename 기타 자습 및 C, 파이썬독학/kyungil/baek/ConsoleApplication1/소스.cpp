#include <iostream>

using namespace std;

class Camera
{
	Camera() {} // �̱����� �����ڴ� �����̹�����
	static Camera *instance;

public:
	static Camera *getInstance();
	void capture() { cout << "ĸ��\n"; }

};


int main12()
{
	Camera* s1 = Camera::getInstance();
	Camera* s2 = Camera::getInstance();
	Camera* s3 = Camera::getInstance();
	s1->capture();
	return 0;



	return 0;
}

Camera * Camera::instance = 0;

Camera * Camera::getInstance()
{
	if (!instance)
	{
		instance = new Camera();
		cout << "ù��° ��ü\n";
		return instance;
	}
	else {
		cout << "������ü ��ȯ\n";
		return instance;
	}
}
