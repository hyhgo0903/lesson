#include "stdafx.h"
#include "Appeal.h"
#include"Boss.h"
void Appeal::EnterState()
{
	_boss->setImg("보스등장");
	_boss->setIndex(0);
}

void Appeal::updateState()
{
	timer++;
	_boss->animaiton(5);

	if (_boss->getImg() == IMAGEMANAGER->findImage("보스등장") && _boss->getIndex() >= _boss->getImg()->getMaxFrameX())
	{
		_boss->setImg("보스일반");
		_boss->setIndex(0);
		timer = 0;
	}
	if (_boss->getImg() == IMAGEMANAGER->findImage("보스일반") /*&& _boss->getIndex() == _boss->getImg()->getMaxFrameX()*/ && timer > 50)
	{
		_boss->setState(MOVE);
	}

}

void Appeal::ExitState()
{
	timer = 0;
}
