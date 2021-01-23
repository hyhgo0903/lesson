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

	_ship->setEmMemoryAddressLink(_em);
	_em->setSpaceShipMemoryAddressLink(_ship);

	_slt = new saveLoadTest;

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
	//_slt->update();
	//collision();
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

