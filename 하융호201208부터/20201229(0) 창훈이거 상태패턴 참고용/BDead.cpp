#include "stdafx.h"
#include "BDead.h"
#include "Boss.h"
void BDead::EnterState()
{

	cout << "몇번>?";
	_boss->setImg("보스죽음");
	if (_boss->getDirec() == 0)_boss->setIndex(0);
	if (_boss->getDirec() == 1)_boss->setIndex(_boss->getImg()->getMaxFrameX());

}

void BDead::updateState()
{

	_boss->animaiton(10);
	if (_boss->getDirec()==0&&_boss->getIndex() >= _boss->getImg()->getMaxFrameX())
	{
		_boss->setPosi(5000, 5000);
	}
	if (_boss->getDirec() == 1 && _boss->getIndex() <= 0)
	{
		_boss->setPosi(5000, 5000);
	}
	_boss->setMAttRC(RectMake(5000, 5000, 1, 1));
}

void BDead::ExitState()
{
}
