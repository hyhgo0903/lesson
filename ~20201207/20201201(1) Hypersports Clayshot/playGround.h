#pragma once
#include "gameNode.h"

#define RELOADCOUNT 70
#define BOWLMAX 20
#define REGENTIME 50

enum SHOOTERSTATE
{
	CENTER,
	LEFT,
	RIGHT
};

struct bowl
{
	RECT rc;
	float xSpd;
	float ySpd;
	float gravity;
	bool isFire;
};


class playGround : public gameNode
{
private:
	image* _background;
	image* _bowlimg;

	SHOOTERSTATE _shooterState; // 플레이어 상태(출력용)

	image* _shooterCenter;
	image* _shooterLeft;
	image* _shooterRight;
	image* _targetImg; // 각종 이미지
	image* _number[10];
	image* _timeUp;

	int _reloadCount; // 장전 카운트

	RECT _leftTarget; // 왼쪽 오른쪽 에임
	RECT _rightTarget;
	RECT _temp; // 충돌판정용
	RECT _reloadRc; // 장전중이면 뜸

	bowl _bowl[BOWLMAX]; // 한 10개쯤?

	bool _isEnd;
	int _randNum;
	int _regenTimer; // 리젠시간
	int _score;
	int _standCount;
	int _leftChaseCount, _rightChaseCount, _tempI;
	int _gameCount;
	float _min;

	RECT _effect[8];

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void left();
	void right();
	void bowlRefill();
	void bowlMove();
	void bowlSpot();
	void effect();
};

