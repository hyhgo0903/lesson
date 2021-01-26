#pragma once
#include "gameNode.h"
#include "bullets.h"
#include <vector>
#include "minion.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	//enemy∫§≈Õø° minion1, 2, 3...¿ª ¥„¿∏∏È µ 
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	bullet* _bullet;

public:
	enemyManager() {};
	~enemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion();

	void minionBulletFire();

	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getViMinion() { return _viMinion; }
	
};

