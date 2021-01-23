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

	//IMAGEMANAGER->addImage("새배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	SCENEMANAGER->addScene("마계씬", new ghostScene);
	SCENEMANAGER->addScene("시바씬", new siva);
	SCENEMANAGER->changeScene("시바씬");
	
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
	//================ 위에 건들지 마라 ==============================
	
	//IMAGEMANAGER->findImage("새배경")->render(getMemDC());
	
	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC(),0,0,CAMX,CAMY, WINSIZEX, WINSIZEY);
}

