#include "stdafx.h"
#include "StartScene.h"
#include <mmsystem.h> //음악 라이브럴리 (중요)
#pragma comment(lib, "winmm.lib") //음악 관련 (중요)
#define START_BGM ".\\sound\\A-Messenger-Is-Needed-_Introduction_.wav"

HRESULT StartScene::init()
{
	start = IMAGEMANAGER->findImage("시작화면");
	sndPlaySound(START_BGM, SND_ASYNC);
	maintime = 0;
	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))SCENEMANAGER->changeScene("메인스테이지");
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
