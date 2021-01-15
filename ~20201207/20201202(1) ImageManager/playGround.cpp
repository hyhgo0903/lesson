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
	gameNode::init();

	setImage();

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();


}

//����(���)�� ����� �ϼ���
void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_background = IMAGEMANAGER->findImage("������");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_background = IMAGEMANAGER->findImage("ŰŰ");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_background = IMAGEMANAGER->findImage("�Ͽ�");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_background = IMAGEMANAGER->findImage("����");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_background = IMAGEMANAGER->findImage("�󷹸��÷���");
	}
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	_background->render(backDC);
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::setImage()
{
	IMAGEMANAGER->addImage("�Ͽ�", "img1.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255)); // Ű���� ���ΰ�
	IMAGEMANAGER->addImage("������", "img2.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ŰŰ", "img3.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "img4.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_background = IMAGEMANAGER->addImage("�󷹸��÷���", "img5.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));


}
