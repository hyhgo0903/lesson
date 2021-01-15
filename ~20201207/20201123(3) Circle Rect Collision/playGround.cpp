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
	
	_x = (_rc2.right + _rc2.left) / 2 - (_rc1.right + _rc1.left) / 2;
	_y = (_rc2.top + _rc2.bottom) / 2 - (_rc1.top + _rc1.bottom) / 2;
	// if (x<0) x = -x; <<�߾��µ� ������ �����ҰŶ� �ʿ����
	_h = _x * _x + _y * _y;

	//�񱳿� ���������� ���� ����
	_rr = (_rc2.right - _rc2.left)/2 + (_rc1.right - _rc1.left)/2;
	_rr *= _rr;
	_cc = ((_rc1.right - _rc1.left) / 2) *((_rc1.right - _rc1.left) / 2);

	_edge1 = ((_rc1.right + _rc1.left) / 2 - _rc2.right) *
		((_rc1.right + _rc1.left) / 2 - _rc2.right) 
		+ // ���������� �簢�� right������ �Ÿ� ����
		((_rc1.top + _rc1.bottom) / 2 - _rc2.top) *
		((_rc1.top + _rc1.bottom) / 2 - _rc2.top);
		 // ���������� �簢�� top������ �Ÿ� ����
	_edge2 = ((_rc1.right + _rc1.left) / 2 - _rc2.right) *
		((_rc1.right + _rc1.left) / 2 - _rc2.right) 
		+
		((_rc1.top + _rc1.bottom) / 2 - _rc2.bottom) *
		((_rc1.top + _rc1.bottom) / 2 - _rc2.bottom);
	_edge3 = ((_rc1.right + _rc1.left) / 2 - _rc2.left) *
		((_rc1.right + _rc1.left) / 2 - _rc2.left)
		+
		((_rc1.top + _rc1.bottom) / 2 - _rc2.bottom) *
		((_rc1.top + _rc1.bottom) / 2 - _rc2.bottom);
	_edge4 = ((_rc1.right + _rc1.left) / 2 - _rc2.left) *
		((_rc1.right + _rc1.left) / 2 - _rc2.left) 
		+
		((_rc1.top + _rc1.bottom) / 2 - _rc2.top) *
		((_rc1.top + _rc1.bottom) / 2 - _rc2.top);

}



//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	if (_h < _rr || (_edge1< _cc || _edge2 < _cc
		|| _edge3 < _cc || _edge4 < _cc)) // �浹 �Ѱ�
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
		Ellipse(backDC, _rc1);
		Rectangle(backDC, _rc2);
		SelectObject(backDC, oldBrush);
		DeleteObject(brush);		
	}
	else
	{
		Ellipse(backDC, _rc1);
		Rectangle(backDC, _rc2);
	}


	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
