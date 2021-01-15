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
	_reloadCount = 0;
	_score = 0;
	_leftLife = 10;
	_isStand = _animation = false;
	_randNum = 0;
	_direction = 1;


	_player = RectMake(WINSIZEX / 2, WINSIZEY - 150, 50, 50);
	for (int i = 0; i < 50; i++)
	{
		_playerBullet[i].rc = { WINSIZEX+1, 0, 0,0 };
		_playerBullet[i].x = 0;
		_playerBullet[i].y = 10;
	}
	
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
	OffsetRect(&_effect[0], 28, 0);		OffsetRect(&_effect[1], 0, 28);	OffsetRect(&_effect[2], 20, 20);
	OffsetRect(&_effect[3], -28, 0);	OffsetRect(&_effect[4], -20, -20);	OffsetRect(&_effect[5], 0, -28);
	OffsetRect(&_effect[6], 20, -20);	OffsetRect(&_effect[7], -20, 20);
	for (int i = 0; i < 50; i++)
	{
		OffsetRect(&_playerBullet[i].rc, _playerBullet[i].x, -_playerBullet[i].y);
	}

	
	if (_leftLife > 0) // ���������
	{
		_reloadCount++; // �ð���


		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.left>0)
		{
			OffsetRect(&_player, -5, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player.right < WINSIZEX)
		{
			OffsetRect(&_player, 5, 0);
		}
		if ((KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown(VK_SPACE)) && _reloadCount>5)
		{
			if (_reloadCount > 50)
			{
				for (int j = 0; j < 10; j++)
				{
					for (int i = 0; i < 50; i++)
					{
						if (_playerBullet[i].rc.bottom < 0 ||
							_playerBullet[i].rc.top > WINSIZEY ||
							_playerBullet[i].rc.right < 0 ||
							_playerBullet[i].rc.left > WINSIZEX) // ȭ�� �ۿ� ������ �̿��Ϸ���
						{
							_playerBullet[i].rc = { _player.left + 15,_player.top,_player.right - 15,_player.bottom - 30 };
							_playerBullet[i].x = rand() % 41 - 20; // -7~7
							_playerBullet[i].y = rand() % 30 + 15;
							break;
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 50; i++)
				{

					if (_playerBullet[i].rc.bottom < 0 ||
						_playerBullet[i].rc.top > WINSIZEY ||
						_playerBullet[i].rc.right < 0 ||
						_playerBullet[i].rc.left > WINSIZEX) // ȭ�� �ۿ� ������ �̿��Ϸ���
					{
						_playerBullet[i].rc = { _player.left + 15,_player.top,_player.right - 15,_player.bottom - 30 };
						_playerBullet[i].x = rand() % 41 - 20; // -7~7
						_playerBullet[i].y = rand() % 30 + 15;
						break;
					}
				}
			}

			_reloadCount = 0;
		}
	}
	if (_leftLife == 0 && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // �����
		this->init();
	}

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	if (_reloadCount > 50)
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _player);
		SelectObject(backDC, oldBrush);
		DeleteObject(brush);
	}
	else Rectangle(backDC, _player);
	for (int i = 0; i < 8; i++)
	{
		Rectangle(backDC,_effect[i]);
	}
	for (int i = 0; i < 50; i++)
	{
		Rectangle(backDC, _playerBullet[i].rc);
	}
/*
	char str[256];	
	sprintf_s(str, "���� ��ȸ : %d (������ ��ȸ ���ư�)", _leftLife);
	TextOut(backDC, WINSIZEX - 300, 20, str, strlen(str));
	if (_leftLife > 0) {
		sprintf_s(str, "�ְ� ��� : %d", _highScore);
		TextOut(backDC, 50, 20, str, strlen(str));
		sprintf_s(str, "���� Ƚ�� : %d", _score);
		TextOut(backDC, 50, 40, str, strlen(str));
	}
	
	if (!_isStand && _leftLife > 0)
	{
		sprintf_s(str, "Ready? : %d", 10-_timeCount/10);
		TextOut(backDC, WINSIZEX/2-50, WINSIZEY/2, str, strlen(str));
	}
	if (_leftLife == 0)
	{
		sprintf_s(str, "���� ��� : %d", _score);
		TextOut(backDC, WINSIZEX / 2 - 60, WINSIZEY / 2 - 40, str, strlen(str));
		sprintf_s(str, "(�ְ� ��� : %d)", _highScore);
		TextOut(backDC, WINSIZEX / 2 - 64, WINSIZEY / 2 - 20, str, strlen(str));
		sprintf_s(str, "������Ϸ��� ENTER");
		TextOut(backDC, WINSIZEX / 2 - 90, WINSIZEY / 2, str, strlen(str));
	}*/

	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
