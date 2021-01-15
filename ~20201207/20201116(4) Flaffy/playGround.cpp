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

	_pipeCount = 0;
	
	_x = 100;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, 80, 80);
	_jumpPower = 0;
	_gravity = 0.1f;
	_isDead = false;
	_isJump = _isStart = true;
	rcR = RND->getFromIntTo(200, 255);
	rcG = RND->getFromIntTo(200, 255);
	rcB = RND->getFromIntTo(200, 255);
	for (int i = 0; i < 2; i++)
	{
		pipeR[i] = RND->getFromIntTo(100, 250);
		pipeG[i] = 255;
		pipeB[i] = RND->getFromIntTo(100, 250);
	}


	for (int i = 0; i < 2; i++)
	{
		_pipeUp[i] = { WINSIZEX + (i *(WINSIZEX/2+40)) , 0,
			WINSIZEX + (i *(WINSIZEX / 2 + 40)) +80, RND->getFromIntTo(0,WINSIZEY - INTERVAL) };
		_pipeDown[i] = { WINSIZEX + (i *(WINSIZEX / 2 + 40)) , _pipeUp[i].bottom+ INTERVAL,
			WINSIZEX + (i *(WINSIZEX / 2 + 40)) + 80, WINSIZEY };
	}

	return S_OK;
}

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	
}

//����(���)�� ����� �ϼ���8
void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (!_isStart)
		{
			_isStart = true;
		}
		if (_isStart && _isDead)
		{
			this->init();
		}
	}
	/*if (KEYMANAGER->isStayKeyDown('A')) _x -= 5;
	if (KEYMANAGER->isStayKeyDown('D')) _x += 5;*/
	if (!_isDead && _isStart)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_isJump = true;
			_jumpPower = 5;
		}

		if (_isJump)
		{
			_y -= _jumpPower;
			_jumpPower -= _gravity;
		}


		for (int i = 0; i < 2; i++) // �̵���Ű�� �浹ó��
		{
			_pipeUp[i].right -= 5;		_pipeUp[i].left -= 5;
			_pipeDown[i].right -= 5;	_pipeDown[i].left -= 5;

			RECT temp;	RECT temp2;
			if (IntersectRect(&temp, &_rc, &_pipeUp[i]) || IntersectRect(&temp2, &_rc, &_pipeDown[i]))
			{
				_isDead = true;
				if (_highCount < _pipeCount) _highCount = _pipeCount;
				rcR = 255;
				rcG = 0;
				rcB = 0;
			}

			if (_pipeUp[i].right < 0)
			{
				_pipeUp[i] = { WINSIZEX , 0,  WINSIZEX + 80, RND->getFromIntTo(0,WINSIZEY - INTERVAL) };
				_pipeDown[i] = { WINSIZEX , _pipeUp[i].bottom + INTERVAL, WINSIZEX + 80, WINSIZEY };
				pipeR[i] = RND->getFromIntTo(100, 255);
				pipeG[i] = RND->getFromIntTo(100, 255);
				pipeB[i] = RND->getFromIntTo(100, 255);
				_pipeCount++;
			}

			if (_y > WINSIZEY + 40 && // �Ʒ���
				_pipeDown[i].left<_rc.right)
			{
				_isDead = true;
				if (_highCount < _pipeCount) _highCount = _pipeCount;
				rcR = 255;
				rcG = 0;
				rcB = 0;
			}
			if (_y < -40 && _pipeUp[i].left < _rc.right) //������
			{
				_isDead = true;
				if (_highCount < _pipeCount) _highCount = _pipeCount;
				rcR = 255;
				rcG = 0;
				rcB = 0;
			}
		}

		_rc = RectMakeCenter(_x, _y, 80, 80); // ũ�� ����(��׷������ʰ�)
	}
	else
	{	
	}
	



}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{

	HBRUSH brush = CreateSolidBrush(RGB(rcR, rcG, rcB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	Rectangle(hdc, _rc);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

	for (int i = 0; i < 2; i++)
	{
		HBRUSH brush = CreateSolidBrush(RGB(pipeR[i], pipeG[i], pipeB[i]));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, _pipeUp[i]);
		Rectangle(hdc, _pipeDown[i]);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}



	sprintf_s(str, "�÷���");
	TextOut(hdc, _rc.left + 10, _rc.top + 10, str, strlen(str));
	
	if (_isDead)
	{
		sprintf_s(str, "������");
		TextOut(hdc, _rc.left + 10, _rc.top + 30, str, strlen(str));

		sprintf_s(str, "������Ϸ��� ENTER");
		TextOut(hdc, WINSIZEX/2 - 50, WINSIZEY/2, str, strlen(str));
	}

	if (!_isDead)
	{
		sprintf_s(str, "�ΰ�");
		TextOut(hdc, _rc.left + 10, _rc.top + 30, str, strlen(str));
	}

	sprintf_s(str, "���� ���� : %d", _pipeCount);
	TextOut(hdc, WINSIZEX/2-50, 10, str, strlen(str));

	sprintf_s(str, "�ְ� ���� : %d", _highCount);
	TextOut(hdc, WINSIZEX / 2 - 50, 30, str, strlen(str));
}
