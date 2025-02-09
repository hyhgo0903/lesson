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

	SCENEMANAGER->changeScene("스타씬");
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("스타씬");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("셀렉트씬");
	}
	// 씬바뀌었을때 연산안함(ex배틀무빙X)
	// -> 프로시저에서 빠지므로 메세지가 안 던져지는것(업데이트X)
	// 씬을쓰면 독립적인 공간으로 이용할 수 있음
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

