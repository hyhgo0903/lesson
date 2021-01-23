#include "stdafx.h"
#include "BossStage.h"

void BossStage::BSPC()
{
	probeDY = _messenger->getPosi().y +_messenger->getMainImg()->getFrameHeight() / 2;
	probeUY = _messenger->getPosi().y - _messenger->getMainImg()->getFrameHeight() / 2;

	//»¡°­ ¹Ù´Ú°ú Ãæµ¹(¹Ù´Ú ÆÇÁ¤)
	for (int i = probeDY - 10;i < probeDY + 3;++i)
	{
		COLORREF color = GetPixel(BossCol->getMemDC(), probeX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 0 && b == 0)
		{
			_messenger->setPosi(_messenger->getPosi().x, i - _messenger->getMainImg()->getFrameHeight() / 2 - 1);
			_messenger->setGravity(0);
			if (_messenger->getPosition() != GROUND)_messenger->setPosition(GROUND);
			_messenger->setDJump(false);
			break;
		}
		if (!(r == 255 && g == 0 && b == 0) && _messenger->getPosition() != CLIFF)
		{
			_messenger->setPosition(AIR);
		}
	}
	for (int i = _boss->getRC().bottom - 10;i < _boss->getRC().bottom;++i)
	{
		COLORREF color = GetPixel(BossCol->getMemDC(), probeX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 0 && b == 0)
		{
			if (_boss->getJPower() < _boss->getGravity())
			{
				_boss->setPosi(_boss->getPosi().x, i - _boss->getImg()->getFrameHeight());
				_boss->setJPower(0);
				_boss->setGravity(0);
				if (_boss->getPrev() == BJUMP)_boss->setState(SPATTERN);
				if (_boss->getPrev() == BDJUMP)
				{
					_boss->setState(MOVE);
				}
			}
		}
	}
}
