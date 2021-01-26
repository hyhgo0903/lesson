#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("�����", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ѿ�", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 1536, 79, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ư", "button.bmp", 0, 0, 122, 62, 1, 2, true, RGB(255, 0, 255));

	SCENEMANAGER->addScene("�׽�Ʈ��", new testScene);
	SCENEMANAGER->addScene("�����", new ghostScene);

	SCENEMANAGER->changeScene("�����");
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown('2'))
	{		
		SCENEMANAGER->changeScene("�׽�Ʈ��");
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("�����");
	}
	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	IMAGEMANAGER->findImage("�����")->render(getMemDC());
	
	
	SCENEMANAGER->render();


	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

