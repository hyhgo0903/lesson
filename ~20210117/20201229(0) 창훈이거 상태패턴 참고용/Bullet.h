#pragma once
#include "gameNode.h"
#include<vector>
struct tagBullet
{
	image* bulletImage;		//총알의 이미지
	RECT rc;				//총알충돌에 사용될 렉트
	float x, y;				//중점 좌표
	int width;
	int height;
	float speed;			//스피드
	float fireX, fireY;		//발사위치
	bool isFire;			//발사했누?
	int count;				//프레임 이미지 카운트용
	int direction;
};

class Bullet :
    public gameNode
{
private:
	vector<tagBullet>_vBullet;
	vector<tagBullet>::iterator _viBullet;
	const char* _imgName;
	float _range;
	int _bulletMax;
public:
	Bullet() {};
	~Bullet() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render(POINT camera);

	void fire(float x, float y,float speed,int direction);

	void move();

	void removeMissile(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};


