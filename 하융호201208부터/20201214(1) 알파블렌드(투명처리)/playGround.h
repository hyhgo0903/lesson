#pragma once
#include "gameNode.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "saveLoadTest.h"

class playGround : public gameNode
{
private:
	spaceShip* _ship;
	enemyManager* _em;
	saveLoadTest* _slt;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render();	//�׸��� ����

	void collision();

};

