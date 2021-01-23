#include <iostream>

using namespace std;

class Camera
{
	Camera() {} // ½Ì±ÛÅæÀÇ »ı¼ºÀÚ´Â ÇÁ¶óÀÌ¹şÀ¸·Î
	static Camera *instance;

public:
	static Camera *getInstance();
	void capture() { cout << "Ä¸ÃÄ\n"; }

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
		cout << "Ã¹¹øÂ° °´Ã¼\n";
		return instance;
	}
	else {
		cout << "ÀÌÀü°´Ã¼ ¹İÈ¯\n";
		return instance;
	}
}
