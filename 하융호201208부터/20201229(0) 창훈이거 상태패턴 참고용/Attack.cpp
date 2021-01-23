#include "stdafx.h"
#include "Attack.h"
#include"Messenger.h"

void Attack::EnterState()
{
	_messenger->setIsAttack(true);
	switch (_messenger->getPrevState())//���⼭ �� ���¿� ���� ����ġ���� �����Ŵ
	{
	case IDLE:
		_messenger->setMainImg("�����Ϲݰ���");
			break;
	case JUMP:
		_messenger->setMainImg("��������");
		break;
	case DASH:
		_messenger->setNeedSub(true);
		_messenger->setMainImg("�뽬����");
		_messenger->setSubImg("�Ϲݽ�");
		break;
	case SIT:
		_messenger->setPosi(_messenger->getPosi().x, _messenger->getPosi().y + _messenger->getMainImg()->getFrameHeight() / 2);
		_messenger->setMainImg("�ɾư���");
		break;
	case CLIMB:
		_messenger->setMainImg("��������");
		break;
	}
	if (_messenger->getDirec() == RIGHT)_messenger->setCurrentIndex(0);
	if (_messenger->getDirec() == LEFT)_messenger->setCurrentIndex(_messenger->getMainImg()->getMaxFrameX());
}

void Attack::updateState()//�Ȱ��� ������ prevState�� ���� ����ġ���� �����ϰ� ������ ������
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
				if(!_messenger->getIsEnhanced())_messenger->seteffecName("R����2");
				if (_messenger->getIsEnhanced())_messenger->seteffecName("��ȭR����2");
				if (_messenger->getCurIndex() >= _messenger->getMainImg()->getMaxFrameX())//������ �����ٴ°��ݾ�? �������� ���� ���������ϱ�
				{
					_messenger->setCurrentIndex(0);
					_messenger->setState(IDLE);//�� �� ���� ���·� ���ư��� ��� �ǹ���
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
				if (!_messenger->getIsEnhanced())_messenger->seteffecName("L����2");
				if (_messenger->getIsEnhanced())_messenger->seteffecName("��ȭL����2");
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
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("R����1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("��ȭR����1");
			if (_messenger->getCurIndex() >= _messenger->getMainImg()->getMaxFrameX())
			{
				_messenger->setCurrentIndex(0);
				_messenger->setState(JUMP);
			}
		}
		else if (_messenger->getDirec() == LEFT)
		{
			if (!_messenger->getIsEnhanced())_messenger->seteffecName("L����1");
			if (_messenger->getIsEnhanced())_messenger->seteffecName("��ȭL����1");
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
	_messenger->setIsAttack(false);// ATTACK���¿��� �ٸ� ���·� ��ȯ�ɶ� isattack�� ����
}
