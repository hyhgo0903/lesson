#include "stdafx.h"
#include "DeadScene.h"
#include <mmsystem.h> //���� ���̺귲�� (�߿�)
#pragma comment(lib, "winmm.lib") //���� ���� (�߿�)
#define DEATH_BGM ".\\sound\\The-Messenger-_-8-bit-Soundtrack_-Unfortunate-Accident-_Death-Fanfare_ (1).wav"

HRESULT DeadScene::init()
{
	devilimg = IMAGEMANAGER->findImage("�Ǹ�");
	count = 0;
	index = 0;
	sndPlaySound(DEATH_BGM, SND_ASYNC);

	return S_OK;
}

HRESULT DeadScene::init(bool check)
{
	devilimg = IMAGEMANAGER->findImage("�Ǹ�");
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
			if(!ischeck)SCENEMANAGER->changeScene("���ν�������");
			if (ischeck)SCENEMANAGER->changeScene("���ν�������", ischeck);
		}
	}

}

void DeadScene::render()
{
	IMAGEMANAGER->findImage("�������")->render(getMemDC());
	devilimg->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
}
