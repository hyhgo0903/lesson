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

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_rc.left -= 5;
		_rc.right -= 5;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_rc.left += 5;
		_rc.right += 5;
	}


	/*
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_rc.left += 5;
		_rc.right += 5;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_rc.left -= 15;
		_rc.right -= 15;
	}*/

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	
	Rectangle(hdc, _rc);
	
}
