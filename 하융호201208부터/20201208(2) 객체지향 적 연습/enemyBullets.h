#pragma once
#include "gameNode.h"
#include <vector>

struct tagEnemyBullet
{
	image* enemyBulletImage;		//총알의 이미지
	RECT rc;				//총알충돌에 사용될 렉트
	float x, y;				//중점 좌표
	float angle;			//각도
	float radius;			//붼지름
	float speed;			//스피드
	float fireX, fireY;		//발사위치
	bool isFire;			//발사했누?
	int count;				//프레임 이미지 카운트용
};

//미리 생성해두고 발사하는 총알
class enemyBullets : public gameNode
{
private:
	vector<tagEnemyBullet> _vEnemyBullet;
	vector<tagEnemyBullet>::iterator _viEnemyBullet;

	float _range;		// 사거리 용 변수


public:
	enemyBullets() {};
	~enemyBullets() {};

	HRESULT init(int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y);	//발사

	void move();					//이동
};