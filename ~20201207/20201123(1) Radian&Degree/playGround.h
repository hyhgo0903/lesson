#pragma once
#include "gameNode.h"

#define PI 3.14f // 요새는 이렇게만 해도 180도로 인식해준다.

class playGround : public gameNode
{
private:
	//Radian : 호의 길이랑 반지름이 같을때 1라디안이라 함
	//			대략 1라디안 : 57.3도

	//Degree : 라디안 수치가 어렵기 때문에 사람이 편의상 만든 것.

	//PI(3.14) : 180도
	//PI / 2   : 90도
	//PI / 4   : 45도
	//PI / 180 : 1도

	float _radian;
	float _degree;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용



};

