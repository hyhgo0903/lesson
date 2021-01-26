#include "stdafx.h"
#include "MainStage.h"
#include <mmsystem.h> //���� ���̺귲�� (�߿�)
#pragma comment(lib, "winmm.lib") //���� ���� (�߿�)
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
	IMAGEMANAGER->addImage("�����浹��", "image/picColMap.bmp", 3000, 1200, true, RGB(255, 0, 255));
	backGround = IMAGEMANAGER->findImage("���");
	mainMap = IMAGEMANAGER->findImage("���ν�������");
	mainCol = IMAGEMANAGER->findImage("�����浹��");
	messenger = new Messenger;
	messenger->init();
	EM = new enemyManager;
	EM->init();
	EM->setMessengerMemory(messenger);
	devil = IMAGEMANAGER->findImage("�Ǹ�");
	//IM = new ItemManager;
	//IM->setMessengerMemory(messenger);

	sndPlaySound(MAIN_BGM, SND_ASYNC);

	return S_OK;
}

HRESULT MainStage::init(bool Chk)
{
	IMAGEMANAGER->addImage("�����浹��", "image/picColMap.bmp", 3000, 1200, true, RGB(255, 0, 255));
	backGround = IMAGEMANAGER->findImage("���");
	mainMap = IMAGEMANAGER->findImage("���ν�������");
	mainCol = IMAGEMANAGER->findImage("�����浹��");
	messenger = new Messenger;
	messenger->init(Chk);
	EM = new enemyManager;
	EM->init();
	EM->setMessengerMemory(messenger);
	devil = IMAGEMANAGER->findImage("�Ǹ�");
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
	if (KEYMANAGER->isOnceKeyDown(VK_F1))SCENEMANAGER->changeScene("������������");
	if (messenger->getHP() <= 0)
	{
		if (check)SCENEMANAGER->changeScene("�÷��̾��ֱ�", check);
		if(!check)SCENEMANAGER->changeScene("�÷��̾��ֱ�");
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
