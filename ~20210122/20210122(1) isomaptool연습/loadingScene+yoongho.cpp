#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::yoonghoInit()
{	

	for (int i = 0; i < LOADINGMAX / 4; ++i)
	{
		IMAGEMANAGER->addImage("�ε����", "���׿��극����ε�.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_currentCount++;
		Sleep(50);
	}

	for (int i = 0; i < LOADINGMAX / 4; ++i)
	{
		IMAGEMANAGER->addFrameImage("tile", "isoprac.bmp", 448, 32, 7, 1, true, RGB(255, 0, 255));
		_currentCount++;
		Sleep(50);
	}

	for (int i = 0; i < LOADINGMAX / 4; ++i)
	{
		IMAGEMANAGER->addFrameImage("���۸���ũ", "image/unit/zergling/zerglingwalk.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
		_currentCount++;
		Sleep(50);
	}
	for (int i = 0; i < LOADINGMAX / 4; ++i)
	{
		IMAGEMANAGER->addFrameImage("���۸���ũ�Ķ�", "image/unit/zergling/zerglingwalkblue.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
		_currentCount++;
		Sleep(50);
	}
}