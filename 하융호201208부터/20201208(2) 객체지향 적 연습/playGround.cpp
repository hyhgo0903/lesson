#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	_ship = new spaceShip;
	_ship->init();
	_enemy = new enemy;
	_enemy->init();

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_ship);
	SAFE_DELETE(_enemy);
}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();

	_ship->update();
	_enemy->update();
	
}

//제발 여기다 그려라 좀...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	IMAGEMANAGER->findImage("배경")->render(getMemDC());
	_ship->render();
	_enemy->render();

	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

