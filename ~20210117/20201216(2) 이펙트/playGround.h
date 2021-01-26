#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "animationTest.h"
#include "effectTest.h"


class playGround : public gameNode
{
private:
	pixelCollision* _pc;
	animationTest* _at;
	effectTest* _et;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

};

