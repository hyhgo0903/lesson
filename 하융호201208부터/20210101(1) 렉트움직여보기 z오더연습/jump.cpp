#include "stdafx.h"
#include "Jump.h"
#include "player.h"

#define GRAVITY 0.2f

void Jump::EnterState()
{
	_pl->getImgRc() = _pl->getGroundRc();
	_jumpPower = 5;
	// 방향에따라 이미지넣고 인덱스 대충 초기화해줌
}

void Jump::updateState()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_pl->getLeft() = false;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_pl->getLeft() = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_pl->getImgX() -= 3;	_pl->getGroundX() -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_pl->getImgX() += 3;	_pl->getGroundX() += 3;
	}
	_jumpPower -= GRAVITY;
	_pl->getImgY() -= _jumpPower;
	if (_pl->getImgY() > _pl->getGroundY())
	{
		_pl->getImgY() = _pl->getGroundY();
		_pl->setState(IDLE);
	}
}

void Jump::ExitState()
{
}

