#pragma once
#include "gameNode.h"
#include "bullets.h"

//상호참조를 위한 전방선언
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;		//플레이어로 사용될 이미지
	missile* _missile;
	rectMissile* _rm;
	
	enemyManager* _em;

public:
	spaceShip() {};
	~spaceShip() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();

	image* getShipImage() { return _ship; }

	rectMissile* getRm() { return _rm; }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
};

