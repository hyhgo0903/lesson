#pragma once
#include "gameNode.h"

#define PI 3.141592f
#define SNAKEBODY 200
#define RADIUS 30
#define SPEED 10

struct tagObj
{
	float x, y;
	float angle;

	float toX, toY;
	
};

class playGround : public gameNode
{
private:
	tagObj _snake[SNAKEBODY];


public:
	playGround();
	~playGround();
	
	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void bodyMove();

};

