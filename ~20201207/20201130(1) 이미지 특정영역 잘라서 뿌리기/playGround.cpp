#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init();

	_background = new image;
	_background->init("코기.bmp", WINSIZEX, WINSIZEY);
		
	_cameraX = _cameraY = 0;

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();


}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();


	if(KEYMANAGER->isStayKeyDown(VK_LEFT)) _cameraX -= 3;
	if(KEYMANAGER->isStayKeyDown(VK_RIGHT)) _cameraX += 3;
	if(KEYMANAGER->isStayKeyDown(VK_UP)) _cameraY -= 3;
	if(KEYMANAGER->isStayKeyDown(VK_DOWN)) _cameraY += 3;
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	//_background->render(backDC, 0, 0);
	_background->render(backDC,0, 0, _cameraX, _cameraY, 100, 100);
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
