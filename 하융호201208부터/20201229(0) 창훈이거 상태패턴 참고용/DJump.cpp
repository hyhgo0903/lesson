#include "stdafx.h"
#include "DJump.h"
#include "Boss.h"
void DJump::EnterState()
{
	_boss->setImg("보스점프");
	_boss->setJPower(1);
	_boss->setGravity(0.2);
	_boss->setPosi(_boss->getPosi().x, _boss->getPosi().y + 70);
	_boss->setPrev(BDJUMP);
	if (_boss->getDirec() == 0)_boss->setIndex(0);
	if (_boss->getDirec() == 1)_boss->setIndex(_boss->getImg()->getMaxFrameX());
}

void DJump::updateState()
{
	_boss->Jump();
	_boss->animaiton(5);
}

void DJump::ExitState()
{
	if (_boss->getDirec() == 0)
	{
		_boss->setDirec(1);
	}
	if (_boss->getDirec() == 1)_boss->setDirec(0);
}
