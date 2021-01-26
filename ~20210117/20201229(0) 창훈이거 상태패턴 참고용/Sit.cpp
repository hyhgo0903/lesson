#include "stdafx.h"
#include "Sit.h"
#include "Messenger.h"
void Sit::EnterState()
{

	_messenger->setMainImg("전령앉음");
	_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y + _messenger->getMainImg()->getFrameHeight() / 2);
	_messenger->setDJump(false);
}

void Sit::updateState()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_messenger->setCurrentIndex(0);
		_messenger->setDirec(RIGHT);

	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
		_messenger->setDirec(LEFT);

	}
	if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
	{
		if (_messenger->getDirec() == RIGHT)
		{
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("R공격1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("강화R공격1");
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, 0, _messenger->getMainImg()->getFrameWidth() - 10, 50, RIGHT);
			if (_messenger->getIsEnhanced())_messenger->setSubRC(0, 0, _messenger->getMainImg()->getFrameWidth() - 20, 50, RIGHT);
		}
		if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, 0, _messenger->getMainImg()->getFrameWidth() - 10, 50, LEFT);
			if (_messenger->getIsEnhanced()) _messenger->setSubRC(0, 0, _messenger->getMainImg()->getFrameWidth() - 20, 50, LEFT);
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("L공격1");
			if (_messenger->getIsEnhanced()) _messenger->seteffecName("강화L공격1");
		}
		_messenger->setPrevState(SIT);
		_messenger->setState(ATTACK);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_messenger->setDJump(true);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))_messenger->setState(IDLE);
}

void Sit::ExitState()
{
	_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y -_messenger->getMainImg()->getFrameHeight() / 2);
}


