#include"stdafx.h"
#include "MainStage.h"
void MainStage::MSPC()
{
	probeDY = messenger->getPosi().y + messenger->getMainImg()->getFrameHeight() / 2;
	probeUY = messenger->getPosi().y - messenger->getMainImg()->getFrameHeight() / 2;
	probeX = messenger->getPosi().x;

	//빨강 바닥과 충돌(바닥 판정)
	for (int i = probeDY - 10;i < probeDY + 3;++i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), probeX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 0 && b == 0)
		{
			messenger->setPosi(messenger->getPosi().x, i - messenger->getMainImg()->getFrameHeight() / 2 - 1);
			messenger->setGravity(0);
			if (messenger->getPosition() != GROUND)messenger->setPosition(GROUND);
			messenger->setDJump(false);
			break;
		}
		if (!(r == 255 && g == 0 && b == 0) && messenger->getPosition() != CLIFF)
		{
			messenger->setPosition(AIR);
		}
	}

	//민트벽과 충돌(벽타기가능)
	for (int i = probeX + messenger->getMainImg()->getFrameWidth() / 2 - 50;i < probeX + messenger->getMainImg()->getFrameWidth() / 2;++i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getPosi().y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (messenger->getDirec() == RIGHT && r == 64 && g == 255 && b == 255)
		{
			messenger->setPosi(i - messenger->getMainImg()->getFrameWidth() / 2, messenger->getPosi().y);
			if (messenger->getPosition() == AIR)messenger->setPosition(CLIFF);
		}
	}
	for (int i = probeX - messenger->getMainImg()->getFrameWidth() / 2 + 50;i > probeX - messenger->getMainImg()->getFrameWidth() / 2;--i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getPosi().y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (messenger->getDirec() == LEFT && r == 64 && g == 255 && b == 255)
		{
			messenger->setPosi(i + messenger->getMainImg()->getFrameWidth() / 2, messenger->getPosi().y);
			if (messenger->getPosition() == AIR)messenger->setPosition(CLIFF);
		}
	}

	//초록벽과 충돌(벽타기불가)

	for (int i = probeX + messenger->getMainImg()->getFrameWidth() / 2 - 10;i < probeX + messenger->getMainImg()->getFrameWidth() / 2;++i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getPosi().y + messenger->getMainImg()->getFrameHeight() / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (messenger->getDirec() == RIGHT && (r == 0 && g == 255 && b == 0) || (r == 64 && g == 255 && b == 255))
		{
			messenger->setPosi(i - messenger->getMainImg()->getFrameWidth() / 2, messenger->getPosi().y);
		}
	}
	for (int i = probeX - messenger->getMainImg()->getFrameWidth() / 2 + 10;i > probeX - messenger->getMainImg()->getFrameWidth() / 2;--i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getPosi().y + messenger->getMainImg()->getFrameHeight() / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (messenger->getDirec() == LEFT && (r == 0 && g == 255 && b == 0) || (r == 64 && g == 255 && b == 255))
		{
			messenger->setPosi(i + messenger->getMainImg()->getFrameWidth() / 2, messenger->getPosi().y);
		}
	}

	//주황 천장과 충돌(벽타기한계높이)
	for (int i = probeUY + 10;i > probeUY - 10;--i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), messenger->getPosi().x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 100 && b == 0 && messenger->getPosition() == CLIFF)
		{
			messenger->setPosi(messenger->getPosi().x, i + messenger->getMainImg()->getFrameHeight() / 2 + 10);
			messenger->setJumpPower(5);
		}
	}

	for (int i = probeUY + 10;i > probeUY - 10;--i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), messenger->getPosi().x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 255 && b == 0)
		{
			messenger->setPosi(messenger->getPosi().x, i + messenger->getMainImg()->getFrameHeight() / 2 + 10);
		}
	}

	//검정을 어택으로 치게 되면 점프 카운트 초기화
	for (int i = messenger->getsubRC().right;i > (messenger->getsubRC().left + messenger->getsubRC().right) / 2;--i)
	{
		if (!messenger->getIsAttack())continue;
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getsubRC().bottom - 3);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 0 && g == 0 && b == 0)
		{
			messenger->setIsJump(true);
			break;
		}
	}
	for (int i = messenger->getsubRC().top;i < messenger->getsubRC().bottom;++i)
	{
		if (!messenger->getIsAttack())continue;
		COLORREF color = GetPixel(mainCol->getMemDC(), messenger->getsubRC().right, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 0 && g == 0 && b == 0)
		{
			messenger->setIsJump(true);
			break;
		}
	}

	//발판 아래에 보라있으면 다운점프 활성화
	for (int i = probeDY - 10;i < probeDY + 3;++i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), probeX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 180 && g == 0 && b == 255 && !messenger->getDJump())
		{
			messenger->setPosi(messenger->getPosi().x, i - messenger->getMainImg()->getFrameHeight() / 2 - 1);
			messenger->setGravity(0);
			if (messenger->getPosition() != GROUND)messenger->setPosition(GROUND);
			break;
		}

	}

	//가시와 같은 장애물과의 충돌
	for (int i = probeDY - 40;i < probeDY + 3;++i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), probeX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 18 && g == 0 && b == 255 && !messenger->getIsDamaged())
		{
			messenger->setState(DAMAGED);
			messenger->setPosition(AIR);
			messenger->setJumpPower(2.5);
			messenger->setGravity(0.08);
			messenger->setHP(-3);
			CAMERAMANAGER->setTime(20);
			if (messenger->getDirec() == RIGHT)messenger->setPosi(messenger->getPosi().x - 50, messenger->getPosi().y);
			if (messenger->getDirec() == LEFT)messenger->setPosi(messenger->getPosi().x + 50, messenger->getPosi().y);
		}
	}
	for (int i = probeX + messenger->getMainImg()->getFrameWidth() / 2 - 10;i > probeX - messenger->getMainImg()->getFrameWidth() / 2;--i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getPosi().y + 10);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 18 && g == 0 && b == 255 && !messenger->getIsDamaged())
		{
			messenger->setState(DAMAGED);
			messenger->setPosition(AIR);
			messenger->setJumpPower(2.5);
			messenger->setGravity(0.08);
			messenger->setHP(-3);
			CAMERAMANAGER->setTime(20);
			if (messenger->getDirec() == RIGHT)messenger->setPosi(messenger->getPosi().x - 50, messenger->getPosi().y);
			if (messenger->getDirec() == LEFT)messenger->setPosi(messenger->getPosi().x + 50, messenger->getPosi().y);
		}
	}


	//하양과 충돌하면 맵 전환
	for (int i = probeX + messenger->getMainImg()->getFrameWidth() / 2;i > probeX;--i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getPosi().y + 10);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 255 && g == 255 && b == 255)
		{
			char temp[128];
			vector<string> vStr;

			vStr.push_back(itoa(messenger->getHP(), temp, 10));
			vStr.push_back(itoa(messenger->getMP(), temp, 10));
			vStr.push_back(itoa(messenger->getIsEnhanced(), temp, 10));
			TXTDATA->txtSave("MapChange.txt", vStr);
			if(!check)SCENEMANAGER->changeScene("보스스테이지");
			if (check)SCENEMANAGER->changeScene("보스스테이지", check);
		}
	}

	//체크포인트용 와인색 충돌
	for (int i = probeX + messenger->getMainImg()->getFrameWidth() / 2;i > probeX;--i)
	{
		COLORREF color = GetPixel(mainCol->getMemDC(), i, messenger->getPosi().y );
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (r == 100 && g == 0 && b == 100&&!check)
		{
			check = true;
			char temp[128];
			vector<string> vStr2;
			vStr2.push_back(itoa(messenger->getPosi().x, temp, 10));
			vStr2.push_back(itoa(messenger->getPosi().y, temp, 10));
			vStr2.push_back(itoa(messenger->getMP(), temp, 10));
			TXTDATA->txtSave("CheckPoint.txt", vStr2);
		}

	}
	//에너미용 충돌
	for (int i = 0;i < EM->getEneVector().size();i++)
	{
		//enemy와 바닥충돌
		for (int j = EM->getEneVector()[i]->getRC().bottom - 10;j < EM->getEneVector()[i]->getRC().bottom;++j)
		{
			COLORREF color = GetPixel(mainCol->getMemDC(), (EM->getEneVector()[i]->getRC().right + EM->getEneVector()[i]->getRC().left) / 2, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			if (r == 255 && g == 0 && b == 0)
			{
				EM->getEneVector()[i]->setIsGravity(true);
				break;
			}
			else EM->getEneVector()[i]->setIsGravity(false);
		}
		//enemy와 벽 충돌
		for (int j = EM->getEneVector()[i]->getRC().right - 10;j < EM->getEneVector()[i]->getRC().right;++j)
		{
			COLORREF color = GetPixel(mainCol->getMemDC(), j, EM->getEneVector()[i]->getRC().bottom);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			if (EM->getEneVector()[i]->getDirec() == LEFT && (r == 0 && g == 255 && b == 0) || (r == 64 && g == 255 && b == 255))
			{
				EM->getEneVector()[i]->setRECT(j - (EM->getEneVector()[i]->getRC().right - EM->getEneVector()[i]->getRC().left));
				break;
			}

		}
		//enemy와 벽충돌
		for (int j = EM->getEneVector()[i]->getRC().left + 10;j > EM->getEneVector()[i]->getRC().left - 3;--j)
		{
			COLORREF color = GetPixel(mainCol->getMemDC(), j, EM->getEneVector()[i]->getRC().bottom);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			if (EM->getEneVector()[i]->getDirec() == RIGHT && (r == 0 && g == 255 && b == 0) || (r == 64 && g == 255 && b == 255))
			{
				EM->getEneVector()[i]->setRECT(j /*+ (em->getEneVector()[i]->getRC().right - em->getEneVector()[i]->getRC().left)*/);
				//break;
			}

		}
	}



}

