#include "stdafx.h"
#include "MainStage.h"
#include <mmsystem.h> //음악 라이브럴리 (중요)
#pragma comment(lib, "winmm.lib") //음악 관련 (중요)
#define MAIN_BGM ".\\sound\\The-Messenger-OST-_Past_-Hills-of-Destiny-_Autumn-Hills_.wav"

MainStage::MainStage()
{
}

MainStage::~MainStage()
{
}

HRESULT MainStage::init()
{
	gameNode::init();
	IMAGEMANAGER->addImage("메인충돌용", "image/picColMap.bmp", 3000, 1200, true, RGB(255, 0, 255));
	backGround = IMAGEMANAGER->findImage("배경");
	mainMap = IMAGEMANAGER->findImage("메인스테이지");
	mainCol = IMAGEMANAGER->findImage("메인충돌용");
	messenger = new Messenger;
	messenger->init();
	EM = new enemyManager;
	EM->init();
	EM->setMessengerMemory(messenger);
	devil = IMAGEMANAGER->findImage("악마");
	//IM = new ItemManager;
	//IM->setMessengerMemory(messenger);

	sndPlaySound(MAIN_BGM, SND_ASYNC);

	return S_OK;
}

HRESULT MainStage::init(bool Chk)
{
	IMAGEMANAGER->addImage("메인충돌용", "image/picColMap.bmp", 3000, 1200, true, RGB(255, 0, 255));
	backGround = IMAGEMANAGER->findImage("배경");
	mainMap = IMAGEMANAGER->findImage("메인스테이지");
	mainCol = IMAGEMANAGER->findImage("메인충돌용");
	messenger = new Messenger;
	messenger->init(Chk);
	EM = new enemyManager;
	EM->init();
	EM->setMessengerMemory(messenger);
	devil = IMAGEMANAGER->findImage("악마");
	//IM = new ItemManager;
	//IM->setMessengerMemory(messenger);

	sndPlaySound(MAIN_BGM, SND_ASYNC);
	return S_OK;
}

void MainStage::release()
{
	gameNode::release();
}

void MainStage::update()
{
	gameNode::update();
	messenger->update(camera);
	EM->update();
	camera = CAMERAMANAGER->CameraMake(messenger->getPosi().x, messenger->getPosi().y, BOTH, mainMap);
	CAMERAMANAGER->shaking(&camera, 3, 3);
	MSPC();
	MSRC();
	if (KEYMANAGER->isOnceKeyDown(VK_F1))SCENEMANAGER->changeScene("보스스테이지");
	if (messenger->getHP() <= 0)
	{
		if (check)SCENEMANAGER->changeScene("플레이어주금", check);
		if(!check)SCENEMANAGER->changeScene("플레이어주금");
	}
	passedtime = TIMEMANAGER->getWorldTime() - maintime;
	if (passedtime > 70.f)
	{
		sndPlaySound(MAIN_BGM, SND_ASYNC);
		maintime = TIMEMANAGER->getWorldTime();
	}
}

void MainStage::render()
{
	gameNode::render();
	backGround->render(getMemDC(), 0, 0, camera);
	mainMap->render(getMemDC(), 0, 0, camera);
	messenger->render(camera);
	EM->render(camera);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		mainCol->render(getMemDC(), 0, 0, camera);
	}
}
