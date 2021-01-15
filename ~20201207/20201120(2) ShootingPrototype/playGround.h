#pragma once
#include "gameNode.h"

struct tagBullet
{
	RECT rc;
	bool isFire;
};

#define BULLETMAX 30

class playGround : public gameNode
{
private:
	RECT _player1;
	RECT _player2;

	tagBullet _bullet[BULLETMAX];

	RECT _backGauge;
	RECT _frontGauge;

	int _r, _g;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void keyControl();

	void bulletFire();

	void bulletMove();

	void collision();

};

