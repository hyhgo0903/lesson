#pragma once
#include "gameNode.h"

class RealTarget
{
public:
	RECT rc;
	float x;
	float y;
	RealTarget()
	{
		rc = { 0,0,0,0 };
		x = 0;
		y = 0;
	}


};

class playGround : public gameNode
{
private:
	RECT _effect[8]; // 이펙용

	int _timeCount; // 사격이후 or 시간지나서 쓰러진 이후 카운트

	int _leftCount; // 남은 사격횟수
	int _score; // 점수
	int _highScore; // 점수
	int _randNum; // 랜덤값 받음
	float _gravity;
	int _direction;

	bool _isStand; // 표적이 나와있을때
	bool _animation; // 누울지 말지
	bool _offset;

	RealTarget tar;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용
};

