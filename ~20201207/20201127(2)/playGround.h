#pragma once
#include "gameNode.h"

//새를 구성하고 있는 구조체!
struct tagBird
{
	float x, y;			//중점 x,y
	RECT rc;			//충돌용 렉트
	float gravity;		//수민이가 싫어하는 그라비티
	float jumpPower;	//양쌤이 좋아하는 점쁘빠월~
	image* img;			//새 이미지
};

class playGround : public gameNode
{
private:
	image* _background;
	image* _day;
	image* _night;

	bool _isNight;
	int _count;

	tagBird _bird;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용



};

