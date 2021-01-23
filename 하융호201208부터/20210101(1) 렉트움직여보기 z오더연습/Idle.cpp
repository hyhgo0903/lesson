#include "stdafx.h"
#include "Idle.h"
#include "player.h"
void Idle::EnterState()
{
	// 방향에따라 이미지넣고 인덱스 대충 초기화해줌
	//_player->setMainImg("전령일반상태");
	
}

void Idle::updateState()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_pl->getDirMemory() != 1)
		{
			_pl->getDirMemory() = 1;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_pl->getDirMemory() != 2)
		{
			_pl->getDirMemory() = 2;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_pl->getDirMemory() != 3)
		{
			_pl->getDirMemory() = 3;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_pl->getDirMemory() != 4)
		{
			_pl->getDirMemory() = 4;
			_pl->setState(WALK);
		}
		else
		{
			_pl->setState(RUN);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_pl->setState(JUMP);
	}
}

void Idle::ExitState()
{

}
