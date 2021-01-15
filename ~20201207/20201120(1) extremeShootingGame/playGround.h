#pragma once
#include "gameNode.h"
#include "vector"

struct bullet
{
	RECT rc; // _bullet.rc로 쓰자
	float x; // x속도
	float y; // y속도
};

class playGround : public gameNode
{
private:
	RECT _effect[8]; // 이펙용

	RECT _player; // 주인공

	bullet _playerBullet[50]; // 한 50개쯤
	
	int _reloadCount; // 재장전 카운트

	int _leftLife; // 남은 사격횟수
	int _score; // 점수
	int _highScore; // 점수
	int _randNum; // 랜덤값 받음
	int _direction;

	bool _isStand; // 표적이 나와있을때
	bool _animation; // 누울지 말지
	bool _offset;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용
};

