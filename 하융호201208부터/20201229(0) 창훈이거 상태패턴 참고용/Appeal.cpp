#include "stdafx.h"
#include "Appeal.h"
#include"Boss.h"
void Appeal::EnterState()
{
	_boss->setImg("��������");
	_boss->setIndex(0);
}

void Appeal::updateState()
{
	timer++;
	_boss->animaiton(5);

	if (_boss->getImg() == IMAGEMANAGER->findImage("��������") && _boss->getIndex() >= _boss->getImg()->getMaxFrameX())
	{
		_boss->setImg("�����Ϲ�");
		_boss->setIndex(0);
		timer = 0;
	}
	if (_boss->getImg() == IMAGEMANAGER->findImage("�����Ϲ�") /*&& _boss->getIndex() == _boss->getImg()->getMaxFrameX()*/ && timer > 50)
	{
		_boss->setState(MOVE);
	}

}

void Appeal::ExitState()
{
	timer = 0;
}
