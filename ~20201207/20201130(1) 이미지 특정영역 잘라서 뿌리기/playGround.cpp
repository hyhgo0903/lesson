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

	_background = new image;
	_background->init("�ڱ�.bmp", WINSIZEX, WINSIZEY);
		
	_cameraX = _cameraY = 0;

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


	if(KEYMANAGER->isStayKeyDown(VK_LEFT)) _cameraX -= 3;
	if(KEYMANAGER->isStayKeyDown(VK_RIGHT)) _cameraX += 3;
	if(KEYMANAGER->isStayKeyDown(VK_UP)) _cameraY -= 3;
	if(KEYMANAGER->isStayKeyDown(VK_DOWN)) _cameraY += 3;
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	//_background->render(backDC, 0, 0);
	_background->render(backDC,0, 0, _cameraX, _cameraY, 100, 100);
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
