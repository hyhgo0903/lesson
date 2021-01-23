#include "stdafx.h"
#include "BJump.h"
#include "Boss.h"
void BJump::EnterState()
{
	_boss->setImg("보스점프");
	_boss->setJPower(14);
	_boss->setGravity(0.2);
	_boss->setPrev(BJUMP);
	if (_boss->getDirec() == 0)_boss->setIndex(0);
	if (_boss->getDirec() == 1)_boss->setIndex(_boss->getImg()->getMaxFrameX());

}

void BJump::updateState()
{
	_boss->Jump();
	_boss->animaiton(5);
}

void BJump::ExitState()
{
	_boss->setIndex(0);
}
