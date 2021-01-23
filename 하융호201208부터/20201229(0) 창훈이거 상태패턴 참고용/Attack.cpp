#include "stdafx.h"
#include "Attack.h"
#include"Messenger.h"

void Attack::EnterState()
{
	_messenger->setIsAttack(true);
	switch (_messenger->getPrevState())//여기서 그 상태에 따른 스위치문을 실행시킴
	{
	case IDLE:
		_messenger->setMainImg("전령일반공격");
			break;
	case JUMP:
		_messenger->setMainImg("점프공격");
		break;
	case DASH:
		_messenger->setNeedSub(true);
		_messenger->setMainImg("대쉬공격");
		_messenger->setSubImg("하반신");
		break;
	case SIT:
		_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y + _messenger->getMainImg()->getFrameHeight() / 2);
		_messenger->setMainImg("앉아공격");
		break;
	case CLIMB:
		_messenger->setMainImg("붙잡고공격");
		break;
	}
	if (_messenger->getDirec() == RIGHT)_messenger->setCurrentIndex(0);
	if (_messenger->getDirec() == LEFT)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
}

void Attack::updateState()//똑같이 수행을 prevState에 따라 스위치문을 수행하고 동작이 끝나면
{
	switch (_messenger->getPrevState())
	{
	case IDLE:
		if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
		{
			chainAttack = true;
		}
		if (_messenger->getDirec() == RIGHT)
		{
			if (chainAttack)
			{
				if(!_messenger->getIsEnhanced())_messenger->seteffecName("R공격2");
				if (_messenger->getIsEnhanced())_messenger->seteffecName("강화R공격2");
				if (_messenger->getCurIndex() >= _messenger->getMainImg()->getMaxFrameX())//동작이 끝났다는거잖아? 프레임이 끝에 도착했으니까
				{
					_messenger->setCurrentIndex(0);
					_messenger->setState(IDLE);//그 때 원래 상태로 돌아가라 라는 의미임
					chainAttack = false;
				}
			}
			else if (_messenger->getCurIndex() >= 4)
			{
					_messenger->setCurrentIndex(0);
					_messenger->setState(IDLE);					
			}
		}
		else if (_messenger->getDirec() == LEFT)
		{
			if (chainAttack)
			{
				if (!_messenger->getIsEnhanced())_messenger->seteffecName("L공격2");
				if (_messenger->getIsEnhanced())_messenger->seteffecName("강화L공격2");
				if (_messenger->getCurIndex() <= 0)
				{
					_messenger->setCurrentIndex(0);
					_messenger->setState(IDLE);
					chainAttack = false;
				}
			}
			else if (_messenger->getCurIndex() <= 4)
			{
				_messenger->setCurrentIndex(0);
				_messenger->setState(IDLE);
			}
		}
		_messenger->animation();
		break;
	case JUMP:
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_messenger->setPosi(_messenger->getPosi().x + 3, _messenger->getPosi().y);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_messenger->setPosi(_messenger->getPosi().x - 3, _messenger->getPosi().y);
		}

		if (_messenger->getDirec() == RIGHT)
		{
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("R공격1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("강화R공격1");
			if (_messenger->getCurIndex() >= _messenger->getMainImg()->getMaxFrameX())
			{
				_messenger->setCurrentIndex(0);
				_messenger->setState(JUMP);
			}
		}
		else if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("L공격1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("강화L공격1");
			if (_messenger->getCurIndex() <= 0)
			{
				_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
				_messenger->setState(JUMP);
			}
		}
		_messenger->animation();
		break;
	case DASH:
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
			_messenger->setNeedSub(false);
			_messenger->setState(JUMP);
		}

		if (_messenger->getDirec() == RIGHT)
		{
			if (_messenger->getCurIndex() >= _messenger->getMainImg()->getMaxFrameX())
			{
				_messenger->setCurrentIndex(0);
				_messenger->setState(DASH);
			}
		}
		else if (_messenger->getDirec() == LEFT)
		{
			if (_messenger->getCurIndex() <= 0)
			{
				_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
				_messenger->setState(DASH);
			}
		}
		_messenger->animation();
		break;
	case SIT:
		if (_messenger->getDirec() == RIGHT)
		{
			if (_messenger->getCurIndex() >= _messenger->getMainImg()->getMaxFrameX())
			{
				_messenger->setCurrentIndex(0);
				_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y - _messenger->getMainImg()->getFrameHeight() / 2);
				_messenger->setState(SIT);
			}
		}
		else if (_messenger->getDirec() == LEFT)
		{
			if (_messenger->getCurIndex() <= 0)
			{
				_messenger->setCurrentIndex(0);
				_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y - _messenger->getMainImg()->getFrameHeight() / 2);
				_messenger->setState(SIT);
			}
		}
		_messenger->animation();
		break;
	case CLIMB:
		if (_messenger->getDirec() == RIGHT)
		{
			if (_messenger->getCurIndex() >= _messenger->getMainImg()->getMaxFrameX())
			{
				_messenger->setCurrentIndex(0);
				_messenger->setState(CLIMB);
			}
		}
		else if (_messenger->getDirec() == LEFT)
		{
			if (_messenger->getCurIndex() <= 0)
			{
				_messenger->setCurrentIndex(0);
				_messenger->setState(CLIMB);
			}
		}
		_messenger->animation();
		break;
	}

}

void Attack::ExitState()
{
	_messenger->setIsAttack(false);// ATTACK상태에서 다른 상태로 전환될때 isattack을 끈다
}
