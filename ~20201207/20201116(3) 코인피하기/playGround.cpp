#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init();

	_player = RectMakeCenter(WINSIZEX / 2,
		WINSIZEY / 2 + 250, 50, 100);

	for (int i = 0; i < COINMAX; i++)
	{
		_coin[i].rc = RectMakeCenter(25 + i * 30, -100, 15, 15);
		_coin[i].speed = RND->getFromIntTo(3, 10);
	}

	_isStart = _isDead = false;
	
	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	
}

//연산(계산)은 여기다 하세요
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

	if (!_isDead && _isStart)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_player.left -= 5;
			_player.right -= 5;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_player.left += 5;
			_player.right += 5;
		}

		for (int i = 0; i < COINMAX; i++)
		{

			_coin[i].rc.top += _coin[i].speed;
			_coin[i].rc.bottom += _coin[i].speed;

			RECT temp;
			if (IntersectRect(&temp, &_player, &_coin[i].rc))
			{
				_isDead = true;
			}

			if (_coin[i].rc.top > WINSIZEY)
			{
				_coin[i].rc = RectMakeCenter(25 + i * 30, -100, 15, 15);
				_coin[i].speed = RND->getFromIntTo(5, 15);
			}

		}
	}

	

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	char str[256];
	sprintf_s(str, "찬호인것");
	

	Rectangle(hdc, _player);
	TextOut(hdc, _player.left, _player.top, str, strlen(str));

	for (int i = 0; i < COINMAX; i++)
	{
		Ellipse(hdc, _coin[i].rc);
	}

	if (_isDead)
	{
		TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, "게임끝", strlen("게임끝"));
	}
	else
	{

	}

}
