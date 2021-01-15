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

	_rc = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2, 100, 100);
	_speed = 0;

	_r = RND->getInt(255);
	_g = RND->getInt(255);
	_b = RND->getInt(255);

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	
}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();

	_speed += 0.1f;


	if (_rc.right >= WINSIZEX - 50)
	{
		_isCrash = true;
		_r = RND->getInt(255);
		_g = RND->getInt(255);
		_b = RND->getInt(255);
	}
	if (_rc.left < 50)
	{	
		_isCrash = false;
		_r = RND->getInt(255);
		_g = RND->getInt(255);
		_b = RND->getInt(255);
		
	}

	if (!_isCrash)
	{
		_rc.left += _speed;
		_rc.right += _speed;
	}
	else
	{
		_rc.left -= _speed;
		_rc.right -= _speed;
	}
	

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(_r, _g, _b));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	Rectangle(hdc, _rc);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}
