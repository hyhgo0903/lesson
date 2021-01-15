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

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용
};

