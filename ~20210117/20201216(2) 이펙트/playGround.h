#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "animationTest.h"
#include "effectTest.h"


class playGround : public gameNode
{
private:
	pixelCollision* _pc;
	animationTest* _at;
	effectTest* _et;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

