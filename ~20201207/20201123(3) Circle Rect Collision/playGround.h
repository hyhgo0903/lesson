#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc1;
	RECT _rc2;

	POINT _LT;

	int _x, _y, _h;
	// h는 빗변이 아니라 빗변의 제곱임

	int _edge1, _edge2, _edge3, _edge4; // 꼭짓점까지의 거리
	int _rr; // 비교용
	int _cc;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용



};

