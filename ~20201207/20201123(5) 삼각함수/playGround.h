#pragma once
#include "gameNode.h"

#define PI 3.14f

class playGround : public gameNode
{
private:
	float _x, _y;
	float _angle;
	int _speed;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����



};

