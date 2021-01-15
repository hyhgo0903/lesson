#pragma once
#include "gameNode.h"

//새를 구성하고 있는 구조체!
struct tagBird
{
	float x, y;			//중점 x,y
	RECT rc;			//충돌용 렉트
	RECT rc2;			//더 정밀한 충돌판정위해 두개를 이용
	float gravity;		//수민이가 싫어하는 그라비티
	float jumpPower;	//양쌤이 좋아하는 점쁘빠월~
};

class playGround : public gameNode
{
private:
	image* _background;	image* _day;	image* _night; // 배경이미지
	image* _uppipe;	image* _downpipe; // 빠이쁘이미지
	image* _number[10]; // 스코어용 숫자
	image* _restart; // 다소 성의없어 보일지도 모르는 엔터그림

	image* _alki; // 웃는알키
	image* _alki2; // 무표정알키

	RECT _upPipeRc[2]; // 빠이쁘
	RECT _downPipeRc[2];

	RECT _temp; // 인터섹트렉트 판정용

	bool _isNight; // 밤이면
	int _count; // 낮밤위해 카운트
	int _score; // 기둥이 리젠될때마다 스코어오름

	int _upPipeWitch; // 위 파이프 위치를 랜덤으로 갖고올예정
	bool _isDead; // 죽었으면 게임중단

	tagBird _bird;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용



};

