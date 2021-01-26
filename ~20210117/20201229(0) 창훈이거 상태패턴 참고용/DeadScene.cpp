#include "stdafx.h"
#include "DeadScene.h"
#include <mmsystem.h> //음악 라이브럴리 (중요)
#pragma comment(lib, "winmm.lib") //음악 관련 (중요)
#define DEATH_BGM ".\\sound\\The-Messenger-_-8-bit-Soundtrack_-Unfortunate-Accident-_Death-Fanfare_ (1).wav"

HRESULT DeadScene::init()
{
	devilimg = IMAGEMANAGER->findImage("악마");
	count = 0;
	index = 0;
	sndPlaySound(DEATH_BGM, SND_ASYNC);

	return S_OK;
}

HRESULT DeadScene::init(bool check)
{
	devilimg = IMAGEMANAGER->findImage("악마");
	count = 0;
	index = 0;
	ischeck = check;
	return S_OK;
}

void DeadScene::release()
{
}

void DeadScene::update()
{
	count++;
	if (count % 10 == 0)
	{
		devilimg->setFrameX(index);
		index++;
		if (index > devilimg->getMaxFrameX())
		{
			if(!ischeck)SCENEMANAGER->changeScene("메인스테이지");
			if (ischeck)SCENEMANAGER->changeScene("메인스테이지", ischeck);
		}
	}

}

void DeadScene::render()
{
	IMAGEMANAGER->findImage("죽음배경")->render(getMemDC());
	devilimg->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
}
