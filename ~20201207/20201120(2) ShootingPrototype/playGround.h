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

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void keyControl();

	void bulletFire();

	void bulletMove();

	void collision();

};

