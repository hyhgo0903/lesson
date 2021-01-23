#include "stdafx.h"
#include "Dash.h"
#include"Messenger.h"
void Dash::EnterState()
{
	_messenger->setNeedSub(true);//대쉬로넘어왔는데 난 대쉬가 상/하반신이 나뉘어져있어서 이때만 두개의 이미지를 보여주기위해서 쓴거야
	_messenger->setMainImg("상반신");//상태패턴 단점은 getter setter를 미친듯이 많이써야해
	_messenger->setSubImg("하반신");//다 게터세터임 

}

void Dash::updateState()
{
	//여기 보면 대쉬 상태에선 VK_DOWN명령어가 없어서 상태전환이 일어나지 않아 
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))_messenger->setState(IDLE);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_messenger->setPosi(_messenger->getPosi().x + 3, _messenger->getPosi().y);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_messenger->setPosi(_messenger->getPosi().x - 3, _messenger->getPosi().y);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_messenger->setJumpPower(4);
		_messenger->setGravity(0.08);
		_messenger->setPosition(AIR);
		_messenger->setState(JUMP);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_messenger->setState(SIT);
		if (_messenger->getDirec() == RIGHT)_messenger->setCurrentIndex(0);
		if (_messenger->getDirec() == LEFT)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
	{
		if (_messenger->getDirec() == RIGHT)
		{
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("R공격1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("강화R공격1");
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, -10, _messenger->getMainImg()->getFrameWidth(), 40, RIGHT);
			if (_messenger->getIsEnhanced()) _messenger->setSubRC(10, -10, _messenger->getMainImg()->getFrameWidth() + 20, 50, RIGHT);
		}
		if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, -10, _messenger->getMainImg()->getFrameWidth(), 40, LEFT);
			if (_messenger->getIsEnhanced()) _messenger->setSubRC(10, -10, _messenger->getMainImg()->getFrameWidth() + 20, 50, LEFT);
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("L공격1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("강화L공격1");
		}
		_messenger->setPrevState(DASH);
		_messenger->setState(ATTACK);
	}
	_messenger->animation();
}

void Dash::ExitState()
{
	_messenger->setNeedSub(false);

}


