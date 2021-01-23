#include "stdafx.h"
#include "SPattern.h"
#include "Boss.h"
void SPattern::EnterState()
{
	_boss->setIndex(0);
	_boss->setImg("보스패턴");
	cout << _boss->getIndex();
}

void SPattern::updateState()
{
	_boss->PtAni();
	_boss->PMove();
	if (_boss->getMAttRC().left <= 0)
	{
		_boss->setSP(false);

		_boss->setMAttRC(RectMake(5000, 5000, 1, 1));
		_boss->setSubRC(RectMake(5000, 5000, 1, 1));
	}
}

void SPattern::ExitState()
{
	_boss->setFire(false);
}
