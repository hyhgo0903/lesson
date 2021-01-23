#pragma once
#include "gameNode.h"
#include "bullets.h"

class spaceShip : public gameNode
{
private:
	image* _ship;		//�÷��̾�� ���� �̹���
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

