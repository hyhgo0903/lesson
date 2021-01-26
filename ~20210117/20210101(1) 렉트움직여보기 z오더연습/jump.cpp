#include "stdafx.h"
#include "Jump.h"
#include "player.h"

#define GRAVITY 0.2f

void Jump::EnterState()
{
	_pl->getImgRc() = _pl->getGroundRc();
	_jumpPower = 5;
	// ���⿡���� �̹����ְ� �ε��� ���� �ʱ�ȭ����
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

