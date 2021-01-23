#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ���
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("���", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	_ship = new spaceShip;
	_ship->init();
	_enemy = new enemy;
	_enemy->init();

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_ship);
	SAFE_DELETE(_enemy);
}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();

	_ship->update();
	_enemy->update();
	
}

//���� ����� �׷��� ��...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	IMAGEMANAGER->findImage("���")->render(getMemDC());
	_ship->render();
	_enemy->render();

	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

