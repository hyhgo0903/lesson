#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	createMinion(500, 500);
	createMinion(600, 600);
	createMinion(700, 500);
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		createBoss(_ptMouse.x, _ptMouse.y);
	}
}

void enemyManager::render()
{
}

void enemyManager::createMinion(float x, float y)
{
	minion* vminion;
	vminion = new minion;
	vminion->init(x, y);
	_vEnemy.push_back(vminion);
}

void enemyManager::createBoss(float x, float y)
{
	boss* vboss;
	vboss = new boss;
	vboss->init(x,y);
	_vEnemy.push_back(vboss);
}
