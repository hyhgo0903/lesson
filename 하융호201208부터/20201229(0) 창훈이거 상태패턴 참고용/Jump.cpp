#include "stdafx.h"
#include "Jump.h"
#include "Messenger.h"
void Jump::EnterState()
{
	_messenger->setMainImg("전령점프");
	if (_messenger->getDirec() == RIGHT)_messenger->setCurrentIndex(0);
	if (_messenger->getDirec() == LEFT)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
	_messenger->setPosition(AIR);
}

void Jump::updateState()
{

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_messenger->setDirec(RIGHT);
		if (_messenger->getCurIndex() <3)_messenger->setCurrentIndex(3);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_messenger->setDirec(LEFT);
		if (_messenger->getCurIndex() > _messenger->getMainImg()->getMaxFrameX() - 3)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX() - 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_messenger->setPosi(_messenger->getPosi().x - 3, _messenger->getPosi().y);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_messenger->setPosi(_messenger->getPosi().x + 3, _messenger->getPosi().y);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		if (_messenger->getDirec() == RIGHT)
		{
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(0, 0, _messenger->getMainImg()->getFrameWidth() + 10, 80, RIGHT);
			if (_messenger->getIsEnhanced())_messenger->setSubRC(-10, 0, _messenger->getMainImg()->getFrameWidth() + 20, 100, RIGHT);
		}
		if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(0, 0, _messenger->getMainImg()->getFrameWidth() + 10, 80, LEFT);
			if (_messenger->getIsEnhanced())_messenger->setSubRC(-10, 0, _messenger->getMainImg()->getFrameWidth() + 20, 100, LEFT);
		}
		_messenger->setPrevState(JUMP);
		_messenger->setState(ATTACK);
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _messenger->getIsJump())
	{
		_messenger->setJumpPower(5);
		_messenger->setGravity(0.08);
		_messenger->setIsJump(false);
	}
	_messenger->animation();
}

void Jump::ExitState()
{
	jumpPower = 0;
}

