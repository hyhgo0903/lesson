#include "stdafx.h"
#include "playGround.h"

/*
gameNode
 ↓상속
playGround
 ↓참조
spaceShip
 ↓참조
missile
rectMissile
c++객체가 사용가능한 언어이지 객체지향은 아님
코드가 간결편안 보기쉽다
*/

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

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_ship);

}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();

	_ship->update();
	
}

//제발 여기다 그려라 좀...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	

	//매번 getmemdc하는건 비효율 -> 구조부터 고침

	IMAGEMANAGER->findImage("배경")->render(getMemDC());
	_ship->render();

	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

