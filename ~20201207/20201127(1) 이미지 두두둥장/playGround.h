#pragma once
#include "gameNode.h"

#define SNAKEBODY 100

//뱀 구조체
struct tagSnake
{
	float x, y;		//중점좌표
	float angle;	//각도
	float speed;	//스피드
	float radius;	//반지름
};

class playGround : public gameNode
{
private:
	tagSnake _snake[SNAKEBODY];
	image* _background;
	image* _donut;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void snakeMove();

};

