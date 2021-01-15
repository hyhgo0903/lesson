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

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용
};

