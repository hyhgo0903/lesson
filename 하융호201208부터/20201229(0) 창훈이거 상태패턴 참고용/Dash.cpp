#include "stdafx.h"
#include "Dash.h"
#include"Messenger.h"
void Dash::EnterState()
{
	_messenger->setNeedSub(true);//�뽬�γѾ�Դµ� �� �뽬�� ��/�Ϲݽ��� ���������־ �̶��� �ΰ��� �̹����� �����ֱ����ؼ� ���ž�
	_messenger->setMainImg("��ݽ�");//�������� ������ getter setter�� ��ģ���� ���̽����
	_messenger->setSubImg("�Ϲݽ�");//�� ���ͼ����� 

}

void Dash::updateState()
{
	//���� ���� �뽬 ���¿��� VK_DOWN��ɾ ��� ������ȯ�� �Ͼ�� �ʾ� 
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
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("R����1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("��ȭR����1");
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, -10, _messenger->getMainImg()->getFrameWidth(), 40, RIGHT);
			if (_messenger->getIsEnhanced()) _messenger->setSubRC(10, -10, _messenger->getMainImg()->getFrameWidth() + 20, 50, RIGHT);
		}
		if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->setSubRC(20, -10, _messenger->getMainImg()->getFrameWidth(), 40, LEFT);
			if (_messenger->getIsEnhanced()) _messenger->setSubRC(10, -10, _messenger->getMainImg()->getFrameWidth() + 20, 50, LEFT);
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("L����1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("��ȭL����1");
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


