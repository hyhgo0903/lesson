#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//총알의 이미지
	RECT rc;				//총알충돌에 사용될 렉트
	float x, y;				//중점 좌표
	float angle;			//각도
	float radius;			//붼지름
	float speed;			//스피드
	float fireX, fireY;		//발사위치
	bool isFire;			//발사했누?
	int count;				//프레임 이미지 카운트용
};

//공용으로 발사할 수 있는 그러한 총알
class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;
public:
	bullet() {};
	~bullet() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	vector<tagBullet> &getVBullet()				{ return _vBullet; }
	vector<tagBullet>::iterator &getViBullet() { return _viBullet; }
};



//발사될때 생성되는 총알
class rectMissile : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	rectMissile() {};
	~rectMissile() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);

	void move();

	vector<tagBullet> &getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator &getViBullet() { return _viBullet; }
};