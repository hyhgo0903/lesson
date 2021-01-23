#include"stdafx.h"
#include "BossStage.h"
void BossStage::BSRC()
{
	RECT temp;
	if (_messenger->getIsAttack()&&_boss->getCanAtt() && IntersectRect(&temp, &_messenger->getsubRC(), &_boss->getRC()))
	{
		_boss->setDamaged(true);
		if (!_messenger->getIsEnhanced())_messenger->setIsAttack(false);
		_boss->setDtimer(0);
		_boss->setHP(_messenger->getDamage());
	}
	if (!_messenger->getIsDamaged()&&IntersectRect(&temp, &_messenger->getMainRC(), &_boss->getRC()))
	{
		CAMERAMANAGER->setTime(20);
		if (_messenger->getDirec() == RIGHT)_messenger->setPosi(_messenger->getPosi().x - 30, _messenger->getPosi().y);
		if (_messenger->getDirec() == LEFT)_messenger->setPosi(_messenger->getPosi().x + 30, _messenger->getPosi().y);
		_messenger->setState(DAMAGED);
		_messenger->setPosition(AIR);
		_messenger->setJumpPower(2.5);
		_messenger->setGravity(0.08);
		_messenger->setHP(-1);
	}
	if (!_messenger->getIsDamaged()&&(IntersectRect(&temp, &_messenger->getMainRC(), &_boss->getMAttRC())||IntersectRect(&temp,&_messenger->getMainRC(),&_boss->getSAttRC())))
	{
		_messenger->setState(DAMAGED);
		_messenger->setHP(-1);
	}
}
