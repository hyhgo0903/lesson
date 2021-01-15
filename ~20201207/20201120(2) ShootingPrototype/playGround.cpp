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

	_player1 = RectMakeCenter(WINSIZEX / 2 - 400, WINSIZEY / 2, 100, 50);
	_player2 = RectMakeCenter(WINSIZEX / 2 + 400, WINSIZEY / 2, 100, 50);

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].isFire = false;
	}

	_backGauge = RectMakeCenter(WINSIZEX / 2 + 300, 70, 400, 50);
	_frontGauge = RectMakeCenter(WINSIZEX / 2 + 300, 70, 400, 50);

	_r = 0;
	_g = 255;

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

	keyControl();
	
	bulletMove();

	collision();
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	Rectangle(backDC, _player1);
	Rectangle(backDC, _player2);

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue;

		Ellipse(backDC, _bullet[i].rc);
		

	}

	Rectangle(backDC, _backGauge);

	HBRUSH brush = CreateSolidBrush(RGB(_r, _g, 0));

	Rectangle(backDC, _frontGauge);
	FillRect(backDC, &_frontGauge, brush);
	DeleteObject(brush);

	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::keyControl()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_player1.top -= 5;
		_player1.bottom -= 5;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_player1.top += 5;
		_player1.bottom += 5;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) bulletFire();

}

void playGround::bulletFire()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire) continue;
		_bullet[i].rc = RectMakeCenter(_player1.right + 5,
			(_player1.top + _player1.bottom) / 2, 10, 10);
		_bullet[i].isFire = true;
		break;
	}
}

void playGround::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].rc.left > WINSIZEX) _bullet[i].isFire = false;
		if (!_bullet[i].isFire) continue;
		_bullet[i].rc.left += 5;
		_bullet[i].rc.right += 5;

		
	}
}

void playGround::collision()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue;

		RECT temp;
		if (IntersectRect(&temp, &_bullet[i].rc, &_player2))
		{

			_bullet[i].isFire = false;

			if (_frontGauge.left >= _frontGauge.right) return;
			_frontGauge.left += 10;
			if (_frontGauge.right - _frontGauge.left < 250)
			{
				_r = 255;
				_g = 255;
			}
			if (_frontGauge.right - _frontGauge.left < 100)
			{
				_r = 255;
				_g = 0;
			}
			break;
		}
	}

}
