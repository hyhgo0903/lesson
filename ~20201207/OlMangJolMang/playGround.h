#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc;
	float _x, _y;


	RECT _rc2; // 바닥검사용

	RECT _obstacle[3]; // 장애물
	RECT _ground[3]; // 바닥
	int _jumpCount; // 점프가능 횟수
	bool _isStart; // 게임 시작했는지
	bool _isDead; // 죽었는지
	bool _isSlide; // 수구렸는지

	float _jumpPower; // 점프파워
	float _gravity; // 중력

	char str[256];

	int randNum; // 랜덤용변수
	int score, highScore; // 스코어
	STATUS status;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용
};

