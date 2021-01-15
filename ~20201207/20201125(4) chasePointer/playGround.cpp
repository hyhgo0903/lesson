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
	gameNode::init();

	_enemy.x = WINSIZEX / 2;
	_enemy.y = WINSIZEY / 2;
	_enemy.angle = PI / 2;


	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();


}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();

	_player.x = _ptMouse.x;
	_player.y = _ptMouse.y;

	_enemy.angle = getAngle(_enemy.x, _enemy.y, _player.x, _player.y);

	_enemy.x += cosf(_enemy.angle) * 3;
	_enemy.y += -sinf(_enemy.angle) * 3;

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	EllipseMakeCenter(backDC, _enemy.x, _enemy.y, 50, 50);
	EllipseMakeCenter(backDC, _player.x, _player.y, 50, 50);
	
	
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
