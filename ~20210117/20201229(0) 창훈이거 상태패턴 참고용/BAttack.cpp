#include "stdafx.h"
#include "BAttack.h"
#include "Boss.h"
void BAttack::EnterState()
{
	_boss->setImg("보스공격");
	if (_boss->getDirec() == 0)_boss->setIndex(0);
	if (_boss->getDirec() == 1)_boss->setIndex(_boss->getImg()->getMaxFrameX());
	_boss->setCanAtt(true);

	//if(!_boss->getFire())_boss->FIRE();

}

void BAttack::updateState()
{
	_boss->atkAni();
	RECT temp;
	if (IntersectRect(&temp, &_boss->getRC(), &_boss->getMAttRC()))
	{
		_boss->setMAttRC(RectMake(5000, 5000, 1, 1));
		_boss->setCanAtt(false);
	}
	if (_boss->getHP() <= 0)
	{
		if (_boss->getDirec() == 0)_boss->setIndex(0);
		if (_boss->getDirec() == 1)_boss->setIndex(_boss->getImg()->getMaxFrameX());
	}
}

void BAttack::ExitState()
{
	_boss->setFire(false);
	timer = 0;
	_boss->setPrev(BATTACK);
}
