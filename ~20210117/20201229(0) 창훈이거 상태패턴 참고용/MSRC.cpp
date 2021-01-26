#include "stdafx.h"
#include "MainStage.h"

void MainStage::MSRC()
{
	for (int i = 0;i < EM->getEneVector().size();++i)
	{
		RECT temp;
		if (messenger->getIsAttack() && IntersectRect(&temp, &messenger->getsubRC(), &EM->getEneVector()[i]->getRC()))
		{
			messenger->setIsJump(true);
			if (!messenger->getIsEnhanced())messenger->setIsAttack(false);
			EM->getEneVector()[i]->setAlpha(100);
			EM->getEneVector()[i]->setHP(1);
			if (EM->getEneVector()[i]->getDirec() == RIGHT)EM->getEneVector()[i]->setRECT(EM->getEneVector()[i]->getRC().left + 20);
			if (EM->getEneVector()[i]->getDirec() == LEFT)EM->getEneVector()[i]->setRECT(EM->getEneVector()[i]->getRC().left - 20);
			if (EM->getEneVector()[i]->getHP() <= 0)EM->removeEnemy(i);
			break;
		}
		if (!messenger->getIsDamaged() && IntersectRect(&temp, &messenger->getMainRC(), &EM->getEneVector()[i]->getRC()))
		{
			CAMERAMANAGER->setTime(20);
			if (messenger->getDirec() == RIGHT)messenger->setPosi(messenger->getPosi().x - 40, messenger->getPosi().y);
			if (messenger->getDirec() == LEFT)messenger->setPosi(messenger->getPosi().x + 40, messenger->getPosi().y);
			messenger->setState(DAMAGED);
			messenger->setPosition(AIR);
			messenger->setJumpPower(2.5);
			messenger->setGravity(0.08);
			messenger->setHP(-1);
			break;
		}
	}

	for (int k = 0;k < EM->getRTvector().size();++k)
	{
		RECT temp;
		if (messenger->getIsAttack() && IntersectRect(&temp, &messenger->getsubRC(), &EM->getRTvector()[k]->getRC()))
		{
			messenger->setIsJump(true);
			if(!messenger->getIsEnhanced())messenger->setIsAttack(false);
			EM->getRTvector()[k]->setAlpha(100);
			EM->getRTvector()[k]->setHP(1);
			if (EM->getRTvector()[k]->getHP() <= 0)EM->removeRT(k);
			break;
		}


		if (!messenger->getIsDamaged() && IntersectRect(&temp, &messenger->getMainRC(), &EM->getRTvector()[k]->getRC()))
		{
			CAMERAMANAGER->setTime(20);
			if (messenger->getDirec() == RIGHT)messenger->setPosi(messenger->getPosi().x - 40, messenger->getPosi().y);
			if (messenger->getDirec() == LEFT)messenger->setPosi(messenger->getPosi().x + 40, messenger->getPosi().y);
			messenger->setState(DAMAGED);
			messenger->setPosition(AIR);
			messenger->setJumpPower(2.5);
			messenger->setGravity(0.08);
			messenger->setHP(-1);
			break;
		}


		for (int j = 0;j < EM->getBullet()->getVBullet().size();j++)
		{
			if (!messenger->getIsDamaged() && IntersectRect(&temp, &messenger->getMainRC(), &EM->getBullet()->getVBullet()[j].rc))
			{
				messenger->setHP(-1);
				messenger->setState(DAMAGED);
				messenger->setJumpPower(2.5);
				messenger->setGravity(0.08);
				EM->getBullet()->removeMissile(j);
				break;
			}
			if (messenger->getIsAttack() && IntersectRect(&temp, &messenger->getsubRC(), &EM->getBullet()->getVBullet()[j].rc))
			{
				messenger->setIsJump(true);
				messenger->setIsAttack(false);
				EM->getBullet()->removeMissile(j);
				break;
			}
		}
	}
}