#pragma once
#include "gameNode.h"

#define PI 3.14f
#define BULLETMAX 200
#define BULLETSIZE 5

struct Bullet
{
	RECT rc;
	double spdX;
	double spdY;
	bool isFire;
	double x, y;
};

class playGround : public gameNode
{
private:
	double _angle;
	const double _speed = 25.;
	const double _gravity = 0.5;
	double _wind = 0.5;
	Bullet _bullet[BULLETMAX];

	int _regenCount;
	int _score;
	RECT _target;
	bool _isStand;
	RECT temp;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void cannon();
	void cannonMove();

};

