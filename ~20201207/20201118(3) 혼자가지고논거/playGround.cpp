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
	_rc = RectMakeCenter(50, WINSIZEY / 4, 80, 80);
	_ground[0] = RectMakeCenter(100, WINSIZEY -400, 1400, 100);
	_ground[1] = RectMakeCenter(800, WINSIZEY - 200, 100, 1000);
	
	score = 0;

	_isStart = true;
	_isDead = false; // �ʱⰪ
	_jumpCount = 2; // �������� Ƚ��
	_xchook = 10;
	_jumpPower = 10;
	_gravity = 0.5f;
	_machal = 0.06f;
	status = GROUND;


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
	RECT temp;
	OffsetRect(&_rc, _xchook, - _jumpPower);
	_jumpPower -= _gravity;
	if (_xchook < 0.02 && _xchook > -0.02) _xchook = 0;
	else if (_xchook > 0) _xchook -= _machal;
	else if (_xchook < 0) _xchook += _machal;

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		this->init();
	}
	if (IntersectRect(&temp, &_rc, &_ground[0]))
	{		// ������ ������
		OffsetRect(&_rc, 0, -(temp.bottom - temp.top));
		if (_jumpPower < 4 && _jumpPower >-4) _jumpPower = 0;
		_jumpPower *= -0.7;
	}
	if (IntersectRect(&temp, &_rc, &_ground[1]))
	{		// ���ʿ��� ������
		OffsetRect(&_rc, -(temp.right - temp.left), 0);
		_xchook *= -0.7;
	}
	//_rc = RectMake(_rc.left, _rc.top, 80, 80);
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	Rectangle(backDC, _rc);
	for (int i = 0; i<3; i++) Rectangle(backDC, _ground[i]);

	//================= �Ʒ��� �ǵ��� ���� ==============================

	this->getBackBuffer()->render(hdc, 0, 0);
}
