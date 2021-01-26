#pragma once
#include "gameNode.h"
#include "spaceShip.h"

class playGround : public gameNode
{
private:
	spaceShip* _ship;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render();	//�׸��� ����

};

