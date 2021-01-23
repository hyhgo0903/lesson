#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy", "ufo.bmp", 0, 0, 530, 32, 10, 1, true, RGB(255, 0, 255));
	

	_ship = new spaceShip;
	_ship->init();

	_em = new enemyManager;
	_em->init();
	_em->setMinion();

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_ship);
	SAFE_DELETE(_em);
}

void playGround::update()
{
	gameNode::update();

	_ship->update();
	_em->update();
	collide();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	IMAGEMANAGER->findImage("배경")->render(getMemDC());
	_ship->render();
	_em->render();

	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

void playGround::collide()
{
	// 나랑 적총알 충돌
	for (_em->getBullet()->getViBullet() = _em->getBullet()->getVBullet().begin();
		_em->getBullet()->getViBullet() != _em->getBullet()->getVBullet().end();)
	{
		RECT temp;
		RECT pRc = _ship->getRect();
		RECT eRc = _em->getBullet()->getViBullet()->rc;
		//RECT eRc = (*_em->getViMinion())->getRect();
		if (IntersectRect(&temp, &pRc, &eRc))
		{
			_em->getBullet()->getViBullet()->isFire = false;
		}

		++_em->getBullet()->getViBullet();
	}

	// 내총알이랑 쟤가 충돌
	for (_em->getViMinion() = _em->getVMinion().begin();
		_em->getViMinion() != _em->getVMinion().end();
		++_em->getViMinion())
	{
		for (_ship->getRm()->getViBullet() = _ship->getRm()->getVBullet().begin();
			_ship->getRm()->getViBullet() != _ship->getRm()->getVBullet().end();
			++_ship->getRm()->getViBullet())
		{
			RECT temp;
			RECT pRc = _ship->getRm()->getViBullet()->rc;
			RECT eRc = (*_em->getViMinion())->getRect();
			if (IntersectRect(&temp, &pRc, &eRc))
			{
				_ship->getRm()->getViBullet()->isFire = false;
				(*_em->getViMinion())->disappear();
			}
		}


	}

}
