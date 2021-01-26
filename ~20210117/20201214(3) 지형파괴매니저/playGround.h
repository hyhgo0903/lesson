#pragma once
#include "gameNode.h"
#include "pixelCollision.h"


class playGround : public gameNode
{
private:
	pixelCollision* _pc;
	int _napalmCount;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render();	//�׸��� ����

};

