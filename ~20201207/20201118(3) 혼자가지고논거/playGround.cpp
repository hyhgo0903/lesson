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
	_rc = RectMakeCenter(50, WINSIZEY / 4, 80, 80);
	_ground[0] = RectMakeCenter(100, WINSIZEY -400, 1400, 100);
	_ground[1] = RectMakeCenter(800, WINSIZEY - 200, 100, 1000);
	
	score = 0;

	_isStart = true;
	_isDead = false; // 초기값
	_jumpCount = 2; // 점프가능 횟수
	_xchook = 10;
	_jumpPower = 10;
	_gravity = 0.5f;
	_machal = 0.06f;
	status = GROUND;


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
	RECT temp;
	OffsetRect(&_rc, _xchook, - _jumpPower);
	_jumpPower -= _gravity;
	if (_xchook < 0.02 && _xchook > -0.02) _xchook = 0;
	else if (_xchook > 0) _xchook -= _machal;
	else if (_xchook < 0) _xchook += _machal;

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		this->init();
	}
	if (IntersectRect(&temp, &_rc, &_ground[0]))
	{		// 위에서 쳤을때
		OffsetRect(&_rc, 0, -(temp.bottom - temp.top));
		if (_jumpPower < 4 && _jumpPower >-4) _jumpPower = 0;
		_jumpPower *= -0.7;
	}
	if (IntersectRect(&temp, &_rc, &_ground[1]))
	{		// 왼쪽에서 쳤을때
		OffsetRect(&_rc, -(temp.right - temp.left), 0);
		_xchook *= -0.7;
	}
	//_rc = RectMake(_rc.left, _rc.top, 80, 80);
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	Rectangle(backDC, _rc);
	for (int i = 0; i<3; i++) Rectangle(backDC, _ground[i]);

	//================= 아래도 건들지 마라 ==============================

	this->getBackBuffer()->render(hdc, 0, 0);
}
