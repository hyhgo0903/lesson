#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc1;
	RECT _rc2;

	int x, y, h;
	// h는 빗변이 아니라 빗변의 제곱임
	int rr; // 비교용

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용



};

