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
	IMAGEMANAGER->addImage("배경", "image/uiback.bmp", 340, 520, false, RGB(0,0,0));
	IMAGEMANAGER->addImage("랜덤", "image/random.bmp", 25, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("선택", "image/selected.bmp", 330, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이버튼", "image/playbutton.bmp", 27, 27, false, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("pic", "image/pic.bmp", 1000, 100, 10, 1, false, RGB(0, 0, 0));
	
	IMAGEMANAGER->addImage("한곡", "image/mode1.bmp", 23, 22, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("반복안함", "image/modex.bmp", 23, 22, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("볼륨", "image/volumebar.bmp", 53, 10, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("재생바", "image/playingbar.bmp", 319, 2, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("음소거", "image/silenced.bmp", 16, 14, false, RGB(0, 0, 0));

	SCENEMANAGER->addScene("사운드씬", new myLittleMP3);

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
	
	SCENEMANAGER->render();
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

