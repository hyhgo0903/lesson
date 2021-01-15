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
	_x = 100;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, 80, 80);
	// ���ΰ�

	score = 0;
	_isStart = true;
	_isDead = _isStuck = false; // �ʱⰪ
	_jumpCount = 2; // �������� Ƚ��
	_jumpPower = 0;
	_gravity = 0.3f;
	status = GROUND;


	for (int i = 0; i < 3; i++)
	{
		_ground[i] = RectMakeCenter(i*900, WINSIZEY / 2 +80,
			RND->getFromIntTo(400, 600),80);
	}
	_obstacle[0] = RectMake((2.0 / 3.0) * (WINSIZEX), RND->getFromIntTo(200, 300), 50, 50); // �⺻
	_obstacle[1] = RectMake(WINSIZEX, RND->getFromIntTo(200, 300), 200, 50); // ����
	_obstacle[2] = RectMake((4.0 / 3.0) * WINSIZEX+50, RND->getFromIntTo(150, 250), 50, 150); // ����
	


	/*RECT _rc;
	RECT _obstacle[3]; // ��ֹ�
	RECT _ground[3]; // �ٴ�*/


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

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // ����ۿ���
		if (score > highScore) highScore = score;
		if (!_isStart) _isStart = true;
		if (_isStart&&_isDead) this->init();
	}

	if (!_isDead && _isStart)
	{
		_y -= _jumpPower; _jumpPower -= _gravity; // �⺻����
		for (int i = 0; i < 3; i++)
		{
			_ground[i].left -= 8; _ground[i].right -= 8;
			_obstacle[i].left -= 10; _obstacle[i].right -= 10;
			if (_ground[i].right < 0)
			{
				_ground[i] = RectMakeCenter(2700, WINSIZEY / 2+80,
					RND->getFromIntTo(400, 600), 80);
			}
			if (_obstacle[i].right < 0)
			{
				randNum = RND->getInt(3);
				if (_obstacle[i].right - _obstacle[i].left == 200)
				{
					switch (randNum)
					{
					case 0: _obstacle[i] = RectMake(WINSIZEX, RND->getFromIntTo(200, 300), 50, 50);
						break;
					case 1: _obstacle[i] = RectMake(WINSIZEX, RND->getFromIntTo(200, 300), 200, 50);
						break;
					case 2: _obstacle[i] = RectMake(WINSIZEX, RND->getFromIntTo(150, 250), 50, 150);
						break;
					}
				}
				else
				{
					switch (randNum)
					{
					case 0: _obstacle[i] = RectMake(WINSIZEX + 150, RND->getFromIntTo(200, 300), 50, 50);
						break;
					case 1: _obstacle[i] = RectMake(WINSIZEX + 150, RND->getFromIntTo(200, 300), 200, 50);
						break;
					case 2: _obstacle[i] = RectMake(WINSIZEX + 150, RND->getFromIntTo(150, 250), 50, 150);
						break;
					}

				}
			}
		}		
		
		
		if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
		{ // ����
			if (_jumpCount > 0)
			{ // ����ī��Ʈ�� �־��
				status = AIR;
				_jumpCount--;
				_jumpPower = 10;
				_gravity = 0.3f;
			}
		}

		RECT temp;
		for (int i = 0; i < 3; i++)
		{
			if (IntersectRect(&temp, &_rc, &_ground[i]))
			{
				if (_rc.right > _ground[i].left && _rc.left < _ground[i].left
					&& (temp.right-temp.left)< (temp.bottom - temp.top)) //�ε��� ���̰� �ʺ񺸴� Ŭ��
				{ // ���ʺ��� �浹
					_x = _ground[i].left - 40;
				}
				else if (_rc.right > _ground[i].right && _rc.left < _ground[i].right
					&& (temp.right - temp.left) < (temp.bottom - temp.top)) //�ε��� ���̰� �ʺ񺸴� Ŭ��
				{ // �����ʺ� �浹
					_x = _ground[i].right + 40;
					_isStuck = true;
				}
				else if (_rc.bottom > _ground[i].top && _rc.top < _ground[i].top && _jumpPower>=0)
				{// �Ʒ��� �ε����� ����
					_jumpPower = 0;
					_gravity = 0.0f;
					_y = WINSIZEY / 2;
					status = GROUND;
				}
				else if (_rc.bottom > _ground[i].bottom && _rc.top < _ground[i].bottom)
				{// ���� �ε����� �ӵ� 0�̻��̸� ���ֱ�
					if (_jumpPower > 0)	_jumpPower = 0;
					_y = WINSIZEY / 2+160;
				}
			}
			if (IntersectRect(&temp, &_rc, &_obstacle[i]))
			{
				if (_rc.right > _obstacle[i].left && _rc.left < _obstacle[i].left
					&& (temp.right - temp.left) < (temp.bottom - temp.top)) //�ε��� ���̰� �ʺ񺸴� Ŭ��
				{ // ���ʺ��� �浹
					_x = _obstacle[i].left - 40;
					_isStuck = true;
				}
				else if (_rc.right > _obstacle[i].right && _rc.left < _obstacle[i].right
					&& (temp.right - temp.left) < (temp.bottom - temp.top)) //�ε��� ���̰� �ʺ񺸴� Ŭ��
				{ // �����ʺ� �浹
					_x = _obstacle[i].right + 40;
				}
				else if (_rc.bottom > _obstacle[i].top	&& _rc.top < _obstacle[i].top && _jumpPower>=0)
				{// �Ʒ��� �ε����� ����
					if (_jumpPower < 0) _jumpPower = 0;
					_gravity = 0.0f;
					_y = _obstacle[i].top - 40;
					status = GROUND;
				}
				else if (_rc.bottom > _obstacle[i].bottom && _rc.top < _obstacle[i].bottom)
				{// ���� �ε����� �ӵ� 0�̻��̸� ���ֱ�
					if (_jumpPower > 0)	_jumpPower = 0;
					_y = _obstacle[i].bottom+40;
				}
			}
		}
		_rc2 = RectMakeCenter(_x, _y + 1, 80, 80);//�������ֳ� ������ RECT
		if (status == GROUND &&
			!IntersectRect(&temp, &_rc2, &_obstacle[0]) &&
			!IntersectRect(&temp, &_rc2, &_obstacle[1]) &&
			!IntersectRect(&temp, &_rc2, &_obstacle[2]) &&
			!IntersectRect(&temp, &_rc2, &_ground[0]) &&
			!IntersectRect(&temp, &_rc2, &_ground[1]) &&
			!IntersectRect(&temp, &_rc2, &_ground[2]))
		{
			status == AIR;
			_gravity = 0.3f;
		}
		_rc2 = RectMakeCenter(_x+1, _y, 80, 80);//�����ʿ� �ֳ� ������ RECT
		if (!IntersectRect(&temp, &_rc2, &_obstacle[0]) &&
			!IntersectRect(&temp, &_rc2, &_obstacle[1]) &&
			!IntersectRect(&temp, &_rc2, &_obstacle[2]) &&
			!IntersectRect(&temp, &_rc2, &_ground[0]) &&
			!IntersectRect(&temp, &_rc2, &_ground[1]) &&
			!IntersectRect(&temp, &_rc2, &_ground[2]))
		{
			_isStuck = false;
		}

		if (status == GROUND)
		{
			_jumpCount = 2;
		}
		score++;
		
		if (_x < 100)
		{// ���� �ƴϸ� �̵�
			if (_x < -40)
			{ // ���ʳ� ����
				_isDead = true;
			}
			else
			{ // �� ��ġ ����
				if(status==GROUND) _x += 1;
			}
		}
		if (_y > WINSIZEY + 40)
		{ // ����
			_isDead = true;
		}

	}
	if ((KEYMANAGER->isStayKeyDown(VK_DOWN) && status == GROUND)||
		_isSlide)
	{
		_rc = RectMakeCenter(_x, _y + 20, 80, 40);
	}
	else  _rc = RectMakeCenter(_x, _y, 80, 80);




}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================


	HBRUSH brush = CreateSolidBrush(RGB(255, 120, 120));
	HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
	Rectangle(backDC, _rc);
	SelectObject(backDC, oldBrush);
	DeleteObject(brush);

	for (int i = 0; i < 3; i++)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 150, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _obstacle[i]);
		SelectObject(backDC, oldBrush);
		DeleteObject(brush);
	}
	for (int i = 0; i < 3; i++)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0,255,150));
		HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _ground[i]);
		SelectObject(backDC, oldBrush);
		DeleteObject(brush);
	}
	if (_isDead)
	{
		sprintf_s(str, "������Ϸ��� ENTER");
		TextOut(backDC, WINSIZEX / 2 - 50, WINSIZEY / 2, str, strlen(str));
	}
	sprintf_s(str, "���� ���� : %d", score/10);
	TextOut(backDC, WINSIZEX / 2 - 50, 50, str, strlen(str));
	sprintf_s(str, "�ְ� ���� : %d", highScore/10);
	TextOut(backDC, WINSIZEX / 2 - 50, 30, str, strlen(str));
	sprintf_s(str, "���� : SPACEŰ");
	TextOut(backDC, WINSIZEX - 105, 30, str, strlen(str));
	sprintf_s(str, "������(���� ��������) : ��Ű");
	TextOut(backDC, WINSIZEX - 200, 50, str, strlen(str));
	sprintf_s(str, "���� : ESCŰ");
	TextOut(backDC, WINSIZEX - 200, 70, str, strlen(str));

	//================= �Ʒ��� �ǵ��� ���� ==============================

	this->getBackBuffer()->render(hdc, 0, 0);
}
