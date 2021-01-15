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

	setImage();

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

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_background = IMAGEMANAGER->findImage("깜장이");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_background = IMAGEMANAGER->findImage("키키");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_background = IMAGEMANAGER->findImage("하울");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_background = IMAGEMANAGER->findImage("벼랑");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_background = IMAGEMANAGER->findImage("얼레리꼴레리");
	}
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	_background->render(backDC);
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::setImage()
{
	IMAGEMANAGER->addImage("하울", "img1.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255)); // 키값을 붙인거
	IMAGEMANAGER->addImage("깜장이", "img2.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("키키", "img3.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("벼랑", "img4.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_background = IMAGEMANAGER->addImage("얼레리꼴레리", "img5.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));


}
