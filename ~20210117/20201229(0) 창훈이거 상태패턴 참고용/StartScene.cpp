#include "stdafx.h"
#include "StartScene.h"
#include <mmsystem.h> //���� ���̺귲�� (�߿�)
#pragma comment(lib, "winmm.lib") //���� ���� (�߿�)
#define START_BGM ".\\sound\\A-Messenger-Is-Needed-_Introduction_.wav"

HRESULT StartScene::init()
{
	start = IMAGEMANAGER->findImage("����ȭ��");
	sndPlaySound(START_BGM, SND_ASYNC);
	maintime = 0;
	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))SCENEMANAGER->changeScene("���ν�������");
	passedtime = TIMEMANAGER->getWorldTime() - maintime;
	if (passedtime > 70.f)
	{
		sndPlaySound(START_BGM, SND_ASYNC);
		maintime = TIMEMANAGER->getWorldTime();
	}
}

void StartScene::render()
{
	start->render(getMemDC());
}
