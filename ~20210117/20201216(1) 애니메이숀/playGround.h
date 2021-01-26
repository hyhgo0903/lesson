#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "animationTest.h"


class playGround : public gameNode
{
private:
	pixelCollision* _pc;
	animationTest* _at;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	int _count; // �񱳿�

};

