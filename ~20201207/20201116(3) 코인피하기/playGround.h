#pragma once
#include "gameNode.h"

#define COINMAX 30

struct tagCoin
{
	RECT rc;
	int speed;
};

class playGround : public gameNode
{
private:
	RECT _player;
	tagCoin _coin[COINMAX];
	bool _isDead;
	bool _isStart;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

