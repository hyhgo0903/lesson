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

	IMAGEMANAGER->addImage("배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy", "ufo.bmp", 0, 0, 530, 32, 10, 1, true, RGB(255, 0, 255));
	
	_napalmCount = 0;
	_pc = new pixelCollision;
	_pc->init();


	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();
	// ###############GD매니저 사용례###############
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		GDMANAGER->destroyElipseCenter("언덕",_ptMouse.x, _ptMouse.y, 50);
		//GDMANAGER->destroyElipse("언덕",_ptMouse.x, _ptMouse.y, 50);
		//GDMANAGER->destroyRect("언덕",_ptMouse.x, _ptMouse.y, 50, 50);
		//GDMANAGER->destroyRectCenter("언덕",_ptMouse.x, _ptMouse.y, 50, 50);
	}

	// 네이팜탄은 다 엎어버렸고 아이디어 떠오르면 해볼게영
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//GDMANAGER->napalm("언덕", _ptMouse.x, _ptMouse.y, 50, 3);
	}

	_pc->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	IMAGEMANAGER->findImage("배경")->render(getMemDC());
	
	_pc->render();

	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}

