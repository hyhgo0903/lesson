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

	IMAGEMANAGER->addImage("새배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 1536, 79, 16, 1, true, RGB(255, 0, 255));

	SCENEMANAGER->addScene("셀렉트씬", new selectScene);
	SCENEMANAGER->addScene("스타씬", new starcraftScene);
	SCENEMANAGER->addScene("사운드씬", new soundTestScene);

	SCENEMANAGER->changeScene("사운드씬");
	
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
	
	IMAGEMANAGER->findImage("새배경")->render(getMemDC());
	
	
	SCENEMANAGER->render();


	TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

