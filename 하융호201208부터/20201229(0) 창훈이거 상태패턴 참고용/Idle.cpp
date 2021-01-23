#include "stdafx.h"
#include "Idle.h"
#include"Messenger.h"
void Idle::EnterState()
{
	_messenger->setMainImg("전령일반상태");
	if (_messenger->getDirec() == RIGHT)_messenger->setCurrentIndex(0);
	if (_messenger->getDirec() == LEFT)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
}

void Idle::updateState()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) )
	{
		_messenger->setState(DASH);
		_messenger->setCurrentIndex(0);
		_messenger->setDirec(RIGHT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_messenger->setState(DASH);
		_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
		_messenger->setDirec(LEFT);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_messenger->setJumpPower(4);
		_messenger->setGravity(0.08);
		_messenger->setState(JUMP);
		_messenger->setPosition(AIR);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))_messenger->setState(SIT);
	if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
	{
		if (_messenger->getDirec() == RIGHT)
		{
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("R공격1");
			if (_messenger->getIsEnhanced()) _messenger->seteffecName("강화R공격1");
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, -10, _messenger->getMainImg()->getFrameWidth(), 40, RIGHT);
			if (_messenger->getIsEnhanced())_messenger->setSubRC(10, -10, _messenger->getMainImg()->getFrameWidth()+20, 50, RIGHT);
		}
		if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, -10,_messenger->getMainImg()->getFrameWidth(),40 ,LEFT);
			if (_messenger->getIsEnhanced()) _messenger->setSubRC(10, -10, _messenger->getMainImg()->getFrameWidth() + 20, 50, LEFT);
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("L공격1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("강화L공격1");
		}
		_messenger->setPrevState(IDLE);
		_messenger->setState(ATTACK);
	}
}

void Idle::ExitState()
{

}
