#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

#pragma warning(disable:4996)

//상호참조를 위한 전방선언
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;		//플레이어로 사용될 이미지
	missile* _missile;
	rectMissile* _rm;
	
	enemyManager* _em;

	float _currentHP, _maxHP;

	progressBar* _hpBar;

	int _alphaValue;

public:
	spaceShip() {};
	~spaceShip() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();

	void hitDamage(float damage);

	image* getShipImage() { return _ship; }

	rectMissile* getRm() { return _rm; }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
};

