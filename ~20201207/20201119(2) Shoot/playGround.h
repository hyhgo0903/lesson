#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _target[12]; // 타겟
	RECT _animation; // 쓰러지는거 보여주기용

	const int _rotation[20] = { 0,2,1,0,2,1,0,1,2,1,0,2,1,0,2,1,0,1,2,1 };// 서순
	int _rotationCount; // 어디인지

	int _timeCount; // 사격이후 or 시간지나서 쓰러진 이후 카운트

	int _leftCount; // 남은 사격횟수
	int _score; // 점수
	int _randNum; // 랜덤값 받음

	bool _isStand; // 표적이 나와있을때
	bool _animationDown; // 누울지 말지


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용
};

