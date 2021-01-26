#include "stdafx.h"
#include "spaceShip.h"

HRESULT spaceShip::init()
{
	_ship = IMAGEMANAGER->addImage("플레이어", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);

	
	_rm = new rectMissile;
	_rm->init(300, WINSIZEY);

	return S_OK;
}

void spaceShip::release()
{
}

void spaceShip::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_rm->fire(_ship->getCenterX(), _ship->getY() - 20);
	}
	_rc = RectMake(_ship->getX(), _ship->getY(), _ship->getWidth(), _ship->getHeight());
	_rm->update();
}

void spaceShip::render()
{
	_ship->render(getMemDC(), _ship->getX(), _ship->getY());

	_rm->render();
}

void spaceShip::collideSpace(enemyManager* _em)
{
	// 나랑 적총알 충돌
	for (_em->getBullet()->getViBullet() = _em->getBullet()->getVBullet().begin();
		_em->getBullet()->getViBullet() != _em->getBullet()->getVBullet().end();)
	{ 
		RECT temp;
		RECT eRc = _em->getBullet()->getViBullet()->rc;
		//RECT eRc = (*_em->getViMinion())->getRect();
		if (IntersectRect(&temp, &_rc, &eRc))
		{
			_em->getBullet()->getViBullet()->isFire = false;
		}

		++_em->getBullet()->getViBullet();
	}
}