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

	_rc1 = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 200, 200);

	

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

	_rc2 = RectMakeCenter(_ptMouse.x, _ptMouse.y, 100, 100);
	
	x = (_rc2.right + _rc2.left) / 2 - (_rc1.right + _rc1.left) / 2;
	y = (_rc2.top + _rc2.bottom) / 2 - (_rc1.top + _rc1.bottom) / 2;
	// if (x<0) x = -x; <<�߾��µ� ������ �����ҰŶ� �ʿ����
	h = x * x + y * y;

	//�񱳿� ���������� ���� ����
	rr = (_rc2.right - _rc2.left)/2 + (_rc1.right - _rc1.left)/2;
	rr *= rr;

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	if (h < rr) // �浹 �Ѱ�
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
		Ellipse(backDC, _rc1);
		Ellipse(backDC, _rc2);
		SelectObject(backDC, oldBrush);
		DeleteObject(brush);		
	}
	else
	{
		Ellipse(backDC, _rc1);
		Ellipse(backDC, _rc2);
	}


	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
