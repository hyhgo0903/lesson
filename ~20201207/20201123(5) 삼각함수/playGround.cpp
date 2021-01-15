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

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_angle = PI / 4;

	_speed = 3;

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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _angle += 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _angle -= 0.04f;
	if(KEYMANAGER->isOnceKeyDown(VK_UP))_speed += 1;
	if(KEYMANAGER->isOnceKeyDown(VK_DOWN))_speed -= 1;

	_x += cosf(_angle) * _speed; // _speed가 cos이 더 크면 철퇴돌리기
	_y += -sinf(_angle) * 2*_speed; // _speed가 sin이 더 크면 둥실둥실
	// 좌표계가 우리가 알던거랑 달라서 (90 <-> 270도) sin대신 -sin을씀


}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	EllipseMakeCenter(backDC, _x, _y, 100, 100);

	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
