#pragma once
#include "gameNode.h"

//��� ������ ���� �� �θ�Ŭ���
class ship : public gameNode
{
protected:
	image* _image;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _speed;
	float _radius;

public:
	ship() {};
	virtual ~ship() {};

	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();
	virtual void keyControl();
	virtual void move();
};

