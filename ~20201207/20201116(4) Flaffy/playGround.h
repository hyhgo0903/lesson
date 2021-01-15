#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc;
	RECT _pipeUp[2];
	RECT _pipeDown[2];

	float _x, _y;

	float _jumpPower;
	float _gravity;
	bool _isJump;
	char str[256];
	int _pipeCount;
	int _highCount = 0;

	bool _isStart;
	bool _isDead;
	int rcR, rcG, rcB = 0;
	int pipeR[2], pipeG[2], pipeB[2] = { 0 };

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

