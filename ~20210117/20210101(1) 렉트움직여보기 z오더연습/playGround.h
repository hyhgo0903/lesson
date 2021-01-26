#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include <vector>

class playGround : public gameNode
{
private:
	enemyManager* _em;
	player* _pl;
	vector<int> bottomY;
	char _str[128];
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

