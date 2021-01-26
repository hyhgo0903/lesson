#include "stdafx.h"
#include "Move.h"
#include "Boss.h"
void Move::EnterState()
{
	_boss->setImg("보스이동");
	if ((_boss->getRC().left + _boss->getRC().right) / 2 < WINSIZEX / 2)_boss->setDirec(1);
	if ((_boss->getRC().left + _boss->getRC().right) / 2 > WINSIZEX / 2)_boss->setDirec(0);
	if (_boss->getDirec() == 0)_boss->setIndex(0);
	if (_boss->getDirec() == 1)_boss->setIndex(_boss->getImg()->getMaxFrameX());
}
void Move::updateState()
{
	timer++;
	_boss->animaiton(10);
	if (_boss->getDirec() == 0)_boss->setPosi(_boss->getPosi().x-1, _boss->getPosi().y);
	if (_boss->getDirec() == 1)_boss->setPosi(_boss->getPosi().x + 1, _boss->getPosi().y);
	if (_boss->getPrev()!=BATTACK&&timer > 70)_boss->setState(BATTACK);
	if (_boss->getPrev() == BATTACK && timer > 50)_boss->setState(BJUMP);
}
void Move::ExitState()
{
	timer = 0;
}
