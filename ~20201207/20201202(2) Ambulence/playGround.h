#pragma once
#include "gameNode.h"

#define REGENTIME 50

struct taxi
{
	RECT rc;
	bool appear;
	float speed; // 상대차도 나름 속도가 있을테니
};


class playGround : public gameNode
{
private:
	image* _backgroundImg;
	image* _ambulImg;
	image* _taxiImg;
	image* _gauge;
	image* _restartImg;
	int _loopX, _loopY;
	image* _number[10];

	RECT _ambul;
	taxi _taxi[5];

	int _regenCount;
	int _appearCount;
	int _randNum;
	int _score;

	RECT _temp; // 충돌판정용

	float _speed; // 앰뷸 속도
	float _oil;
	float _speedAngle;
	float _oilAngle; // 계기판용 앵글
	float _sideSpeed; // 좌우속도(좌우로 받을때)


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void setImage();
	void taxiRegen();
	void collision();
	void taxiTaxiCollision();
	void gaugeAngle();

};

