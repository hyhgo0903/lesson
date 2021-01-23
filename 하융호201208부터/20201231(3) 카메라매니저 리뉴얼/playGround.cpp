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

	//IMAGEMANAGER->addImage("�����", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	SCENEMANAGER->addScene("�����", new ghostScene);
	SCENEMANAGER->addScene("�ùپ�", new siva);
	SCENEMANAGER->changeScene("�ùپ�");
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();


	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	//IMAGEMANAGER->findImage("�����")->render(getMemDC());
	
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC(),0,0,CAMX,CAMY, WINSIZEX, WINSIZEY);
}

