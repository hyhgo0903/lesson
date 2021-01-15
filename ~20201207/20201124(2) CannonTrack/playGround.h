#pragma once
#include "gameNode.h"

#define PI 3.14f
#define BULLETMAX 70
#define TRACKSIZE 1

struct tagBullet
{
	float x, y;		//중점 x, y
	float speed;	//스피드
	float angle;	//각도
	float radius;	//반지름
	bool isFire;	//발쏴했니?
	float gravity;
};

struct tagCannon
{
	POINT center;		//캐논 중점
	POINT cannonEnd;	//캐논 포신 끝점
	int radius;			//반지름
	int cannon;			//포신(?) 길이
	float angle;		//각도
};

class playGround : public gameNode
{
private:
	tagBullet _bullet[BULLETMAX];
	tagCannon _cannon;

	tagBullet _track[BULLETMAX];

	const int _speed = 8; // 총알 스피드는 여기서 (궤적도 같이)

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void bulletFire();
	void bulletMove();

	void trackSet(); // 트랙세팅 함수
};

