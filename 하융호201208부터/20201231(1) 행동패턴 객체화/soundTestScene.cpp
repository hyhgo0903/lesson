#include "stdafx.h"
#include "soundTestScene.h"

HRESULT soundTestScene::init()
{
	SOUNDMANAGER->addSound("�����1", "08_Childish Gambino - Redbone.mp3", true, false);
	SOUNDMANAGER->addSound("�����2", "08_Childish Gambino - Redbone.mp3", true, false);
	SOUNDMANAGER->addSound("�����3", "08_Childish Gambino - Redbone.mp3", true, false);


	return S_OK;
}

void soundTestScene::release()
{

}

void soundTestScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		SOUNDMANAGER->play("�����1", 1.0f);
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SOUNDMANAGER->play("�����2", 0.5f);
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->play("�����3", 0.3f);
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->stop("�����1");
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->stop("�����2");
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		SOUNDMANAGER->stop("�����3");
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		SOUNDMANAGER->pause("�����1");
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		SOUNDMANAGER->pause("�����2");
	}
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		SOUNDMANAGER->pause("�����3");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		SOUNDMANAGER->resume("�����1");
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		SOUNDMANAGER->resume("�����2");
	}
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		SOUNDMANAGER->resume("�����3");
	}
}

void soundTestScene::render()
{
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 100, "�����", strlen("�����"));
}
