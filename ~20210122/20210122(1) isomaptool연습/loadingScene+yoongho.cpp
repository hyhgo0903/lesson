#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::yoonghoInit()
{	

	for (int i = 0; i < LOADINGMAX / 4; ++i)
	{
		IMAGEMANAGER->addImage("로딩배경", "리그오브레전드로딩.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
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
		IMAGEMANAGER->addFrameImage("저글링워크", "image/unit/zergling/zerglingwalk.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
		_currentCount++;
		Sleep(50);
	}
	for (int i = 0; i < LOADINGMAX / 4; ++i)
	{
		IMAGEMANAGER->addFrameImage("저글링워크파랑", "image/unit/zergling/zerglingwalkblue.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
		_currentCount++;
		Sleep(50);
	}
}