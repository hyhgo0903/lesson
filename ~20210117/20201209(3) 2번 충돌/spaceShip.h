#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "enemyManager.h"
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;		//�÷��̾�� ���� �̹���
	rectMissile* _rm;
	RECT _rc;

public:
	spaceShip() {};
	~spaceShip() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getRect() { return _rc; }
	rectMissile* getRm() { return _rm; }

	void collideSpace(enemyManager* _em);
};

