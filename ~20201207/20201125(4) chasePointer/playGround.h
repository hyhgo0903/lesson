#pragma once
#include "gameNode.h"

#define PI 3.14159f

struct tagObj
{
	float x, y;
	float angle;
	
};

class playGround : public gameNode
{
private:
	tagObj _player;
	tagObj _enemy;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	

};

