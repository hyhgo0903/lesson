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

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_angle = PI / 4;

	_speed = 3;

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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _angle += 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _angle -= 0.04f;
	if(KEYMANAGER->isOnceKeyDown(VK_UP))_speed += 1;
	if(KEYMANAGER->isOnceKeyDown(VK_DOWN))_speed -= 1;

	_x += cosf(_angle) * _speed; // _speed�� cos�� �� ũ�� ö�𵹸���
	_y += -sinf(_angle) * 2*_speed; // _speed�� sin�� �� ũ�� �սǵս�
	// ��ǥ�谡 �츮�� �˴��Ŷ� �޶� (90 <-> 270��) sin��� -sin����


}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	EllipseMakeCenter(backDC, _x, _y, 100, 100);

	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
