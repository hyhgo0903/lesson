#pragma once
#include "gameNode.h"
#include "bullets.h"

//��ȣ������ ���� ���漱��
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;		//�÷��̾�� ���� �̹���
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

