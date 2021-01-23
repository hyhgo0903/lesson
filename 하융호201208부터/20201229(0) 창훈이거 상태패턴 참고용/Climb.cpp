#include "stdafx.h"
#include "Climb.h"
#include"Messenger.h"

void Climb::EnterState()
{
	_messenger->setMainImg("���ɺ����");
	if (_messenger->getDirec() == RIGHT)_messenger->setCurrentIndex(0);
	if (_messenger->getDirec() == LEFT)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
	
}

void Climb::updateState()
{

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_messenger->getDirec() == RIGHT)
		{
			_messenger->setPosi(_messenger->getPosi().x - 10, _messenger->getPosi().y);
			_messenger->setPosition(AIR);
			_messenger->setState(JUMP);
			_messenger->setJumpPower(8);
		}
		if (_messenger->getDirec() == LEFT)
		{
			_messenger->setPosi(_messenger->getPosi().x + 10, _messenger->getPosi().y);
			_messenger->setPosition(AIR);
			_messenger->setState(JUMP);
			_messenger->setJumpPower(8);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y - 3);
		_messenger->animation();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y + 3);
		_messenger->animation();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
	{
		if (_messenger->getDirec() == RIGHT)
		{
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("L����1");
			if (_messenger->getIsEnhanced()) _messenger->seteffecName("��ȭL����1");
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(50, 0, 85, 50, LEFT);
			if (_messenger->getIsEnhanced())_messenger->setSubRC(50, 0, 120, 60, LEFT);
		}
		if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(50, 0, 85, 50, RIGHT);
			if (_messenger->getIsEnhanced())_messenger->setSubRC(50, 0, 120, 60, RIGHT);
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("R����1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("��ȭR����1");
		}
		_messenger->setPrevState(CLIMB);
		_messenger->setState(ATTACK);
	}
}

void Climb::ExitState()
{
	_messenger->setGravity(0.3);
	_messenger->setJumpPower(2);
}

