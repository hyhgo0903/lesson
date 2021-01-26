#include "stdafx.h"
#include "Damaged.h"
#include "Messenger.h"
void Damaged::EnterState()
{
	_messenger->setMainImg("ÇÇ°ÝµÊ");
	_messenger->setIsDamaged(true);
	if (_messenger->getDirec() == RIGHT)_messenger->setCurrentIndex(0);
	if (_messenger->getDirec() == LEFT)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());

}

void Damaged::updateState()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)||KEYMANAGER->isOnceKeyDown(VK_LEFT))_messenger->setState(DASH);
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_messenger->setJumpPower(3);
		_messenger->setGravity(0.2);
		_messenger->setState(JUMP);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))_messenger->setState(SIT);
	if (!_messenger->getIsDamaged())_messenger->setState(IDLE);
}

void Damaged::ExitState()
{
}

