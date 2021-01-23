#pragma once
#include"image.h"
#include"singletonBase.h"
#include<map>
enum XY
{
	X,
	Y,
	BOTH
};
enum DEST
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class CameraManager:public singletonBase<CameraManager>
{
private:
	XY WantToBase;
	DEST dest;
	int _time=0;
	int interval=0;
	bool _isShaking = false;
public:
	CameraManager();
	~CameraManager();
	/*ĳ���� ���� �������� ī�޶� ����� ���� �� ����� �Լ�
	WantToBase�� ���ϴ� �� ����. X���� ���������ϰ� �ʹٸ� X, Y���� ���������Ѵٸ� Y, ĳ���Ͱ� �׻� �߾����� ���ϰ� �ʹٸ� BOTH
	backgroundW�� ��� width, backgroundH�� ��� Height*/
	POINT CameraMake(int CharacterX,int CharacterY,XY WantToBase,int backgroundW,int backgroundH);
	//���� ����ȭ�� ī�޶� ����� ���� ��(���� �̱���)
	POINT CameraMake(int CharacterX, int CharacterY, XY WantToBase, int backgroundW, int backgroundH, int seperate, DEST dest);
	//�� �����ϰ� img������ ������ ���� �ǿ�
	POINT CameraMake(int CharacterX, int CharacterY, XY WantToBase, image* img);
	POINT CameraMake(int CharacterX, int CharacterY, XY WantToBase, image* img, int seperate, int check);
	//�̴ϸ� ����� ���� �� ���. background�̹����� ĳ���� �̹���, �̴ϸ�ũ�⸦ ����� ��Ʈ�� ������ ��
	RECT miniMapMake(image* img, image* CharacterImg,RECT rc);
	//ī�޶� ���� �����̴� �̴ϸ��� ����� ������ ���� �̱���
	void miniMapMake(POINT camera, int sizeX, int sizeY,image* characterImg,image* backImg);
	//ī�޶� ������ �ְ�, ���� ���� ������ �������
	void shaking(POINT *camera,int powerX,int powerY );
	//�ð� ����. Ư�� ���ǿ����� ����ǵ��� �ؾ��մϴ� �ȱ׷��� ������ ��鸳�ϴ�
	void setTime(int time);
};

