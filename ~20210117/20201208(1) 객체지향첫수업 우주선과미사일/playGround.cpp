#include "stdafx.h"
#include "playGround.h"

/*
gameNode
 ����
playGround
 ������
spaceShip
 ������
missile
rectMissile
c++��ü�� ��밡���� ������� ��ü������ �ƴ�
�ڵ尡 ������� ���⽱��
*/

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

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_ship);

}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();

	_ship->update();
	
}

//���� ����� �׷��� ��...
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	

	//�Ź� getmemdc�ϴ°� ��ȿ�� -> �������� ��ħ

	IMAGEMANAGER->findImage("���")->render(getMemDC());
	_ship->render();

	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

