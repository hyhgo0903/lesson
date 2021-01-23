#pragma once
#include "gameNode.h"
#include "bullets.h"

class spaceShip : public gameNode
{
private:
	image* _ship;		//플레이어로 사용될 이미지
	missile* _missile;
	rectMissile* _rm;


public:
	spaceShip() {};
	~spaceShip() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

