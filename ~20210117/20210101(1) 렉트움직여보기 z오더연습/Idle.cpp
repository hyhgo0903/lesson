#include "stdafx.h"
#include "Idle.h"
#include "player.h"
void Idle::EnterState()
{
	// ���⿡���� �̹����ְ� �ε��� ���� �ʱ�ȭ����
	//_player->setMainImg("�����Ϲݻ���");
	
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
