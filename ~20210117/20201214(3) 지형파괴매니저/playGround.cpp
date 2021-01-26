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

	IMAGEMANAGER->addImage("���", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
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
	// ###############GD�Ŵ��� ����###############
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		GDMANAGER->destroyElipseCenter("���",_ptMouse.x, _ptMouse.y, 50);
		//GDMANAGER->destroyElipse("���",_ptMouse.x, _ptMouse.y, 50);
		//GDMANAGER->destroyRect("���",_ptMouse.x, _ptMouse.y, 50, 50);
		//GDMANAGER->destroyRectCenter("���",_ptMouse.x, _ptMouse.y, 50, 50);
	}

	// ������ź�� �� ������Ȱ� ���̵�� �������� �غ��Կ�
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//GDMANAGER->napalm("���", _ptMouse.x, _ptMouse.y, 50, 3);
	}

	_pc->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	IMAGEMANAGER->findImage("���")->render(getMemDC());
	
	_pc->render();

	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

