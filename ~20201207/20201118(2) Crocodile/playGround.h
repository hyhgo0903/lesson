#pragma once
#include "gameNode.h"

struct tagBox
{
	RECT rc;
	bool isRotten;
	bool isClicked;
};

class playGround : public gameNode
{
private:
	tagBox _tooth[20];
	bool _isAngry;
	int _down;
	RECT upperItmom;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용
};

