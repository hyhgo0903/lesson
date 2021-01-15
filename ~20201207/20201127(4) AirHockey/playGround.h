#pragma once
#include "gameNode.h"

#define BALLRADIAN 10
#define PLAYERRADIAN 20
#define BALLSPEED 20. // 시작할때랑 충돌시 속도

class playGround : public gameNode
{
private:
	image* _board; // 800*560
	image* _number[10]; // 스코어랑 대기초

	image* _p1win;
	image* _p2win;
	image* _p1img;
	image* _p2img;
	image* _ballimg;

	RECT _temp; // 충돌판정용

	RECT _p1; // 왼쪽 플레이어
	RECT _p2; // 오른쪽 플레이어
	RECT _ball; // 공
	float _ballSpd; // 공속도
	float _ballAngle; // 공각
	float _angle; // 충돌시 겟앵글용

	char str[256];

	int _scoreP1; // 1P점수
	int _scoreP2; // 2P점수

	int _count; // 재시작시 대기용

	int _p1isStanding; // 멈추면 20까지 오르고 움직일때 줄어들음(쳤을때 덜튕겨나감)
	int _p2isStanding; // 멈추면 20까지 오르고 움직일때 줄어들음(쳤을때 덜튕겨나감)

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void playerMove();	//플레이어이동
	void ballMove(); // 공이동
	void collide(); // 쳤을때
	void collideWall(); // 벽부딪
	void scoring(); // 스코어 기록

};

