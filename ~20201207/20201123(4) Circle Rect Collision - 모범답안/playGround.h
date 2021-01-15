#pragma once
#include "gameNode.h"

#define PI 3.14f

class playGround : public gameNode
{
private:
	RECT _rectangle;
	RECT _ellipse;

	bool _isCollision;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	bool isCollision(RECT& rc1, RECT& rc2);

	bool getDistance(RECT& rc, float x, float y);


};

