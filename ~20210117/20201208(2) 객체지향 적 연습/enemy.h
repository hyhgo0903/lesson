#pragma once
#include "gameNode.h"
#include "enemyBullets.h"
#include <vector>

struct tagEnemy
{
	image* enemyImage;
	RECT rc;
	int count;				//프레임 이미지 카운트용
	bool appear;
	int index;
};

class enemy : public gameNode
{
private:
	vector<tagEnemy> _vEnemy;
	vector<tagEnemy>::iterator _viEnemy;
	enemyBullets * _enemyBullets;

public:
	enemy() {};
	~enemy() {};

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};