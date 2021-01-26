#include "stdafx.h"
#include "BossStage.h"
#include <mmsystem.h> //���� ���̺귲�� (�߿�)
#pragma comment(lib, "winmm.lib") //���� ���� (�߿�)
#define BOSS_BGM ".\\sound\\The-Messenger-_-8-bit-Soundtrack_-Abomination-Without-Description (1).wav"

BossStage::BossStage()
{
}

BossStage::~BossStage()
{
}

HRESULT BossStage::init()
{
	backGround = IMAGEMANAGER->findImage("���");
	BossMap = IMAGEMANAGER->findImage("������������");
	BossCol = IMAGEMANAGER->findImage("�����浹��");
	_messenger = new Messenger;
	_messenger->init(PointMake(50,470));
	_boss = new Boss;
	_boss->init();
	camera.x=0;
	camera.y = 0;
	sndPlaySound(BOSS_BGM, SND_ASYNC);
	return S_OK;
}

HRESULT BossStage::init(bool chk)
{
	backGround = IMAGEMANAGER->findImage("���");
	BossMap = IMAGEMANAGER->findImage("������������");
	BossCol = IMAGEMANAGER->findImage("�����浹��");
	_messenger = new Messenger;
	_messenger->init(PointMake(50, 470));
	_boss = new Boss;
	_boss->init();
	camera.x = 0;
	camera.y = 0;
	check = chk;
	sndPlaySound(BOSS_BGM, SND_ASYNC);
	return S_OK;
}

void BossStage::release()
{
}

void BossStage::update()
{
	camera = CAMERAMANAGER->CameraMake(_messenger->getPosi().x, _messenger->getPosi().y, BOTH, BossMap);
	_messenger->update(camera);
	_boss->update();
	BSRC();
	BSPC();
	if (_messenger->getHP() <= 0)
	{
		if(!check)SCENEMANAGER->changeScene("�÷��̾��ֱ�");
		if (check)SCENEMANAGER->changeScene("�÷��̾��ֱ�", check);
	}
	passedtime = TIMEMANAGER->getWorldTime() - maintime;
	if (passedtime > 70.f)
	{
		sndPlaySound(BOSS_BGM, SND_ASYNC);
		maintime = TIMEMANAGER->getWorldTime();
	}
}

void BossStage::render()
{
	backGround->render(getMemDC(),0,0,camera);
	BossMap->render(getMemDC(), 0, 0, camera);
	_boss->render(camera);
	_messenger->render(camera);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		BossCol->render(getMemDC(), 0, 0, camera);
	}
}
