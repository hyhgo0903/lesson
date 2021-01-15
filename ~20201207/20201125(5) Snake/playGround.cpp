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

	_snake[0].angle = PI / 2;
	_snake[0].x = WINSIZEX / 2;
	_snake[0].y = WINSIZEY;

	for (int i = 1; i < SNAKEBODY; i++)
	{
		_snake[i].angle = PI / 2;
		_snake[i].x = WINSIZEX/2;
		_snake[i].y = WINSIZEY + 10 * i;
	}

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();


}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _snake[0].angle += 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _snake[0].angle -= 0.04f;

	if (_snake[0].x < RADIUS)
	{
		_snake[0].x = RADIUS;
		_snake[0].angle = PI - _snake[0].angle;
	}
	if (_snake[0].x > WINSIZEX - RADIUS)
	{
		_snake[0].x = WINSIZEX - RADIUS;
		_snake[0].angle = PI - _snake[0].angle;
	}
	if (_snake[0].y < RADIUS)
	{
		_snake[0].y = RADIUS;
		_snake[0].angle = PI2 - _snake[0].angle;
	}		
	if (_snake[0].y > WINSIZEY - RADIUS)
	{
	_snake[0].y = WINSIZEY - RADIUS;
	_snake[0].angle = PI2 - _snake[0].angle;
	}

	bodyMove();
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	for (int i = SNAKEBODY-1; i >= 0; i-=5)
	{
		EllipseMakeCenter(backDC, _snake[i].x, _snake[i].y, 2*RADIUS, 2 * RADIUS);
	}
	
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::bodyMove()
{
	_snake[0].x += SPEED * cosf(_snake[0].angle);
	_snake[0].y += SPEED * -sinf(_snake[0].angle);
	for (int i = 1; i < SNAKEBODY; i++)
	{
		/*_snake[i].toX = _snake[i - 1].x;
		_snake[i].toY = _snake[i - 1].y;
		_snake[i].x += SPEED * cosf(_snake[i].angle)+;
		_snake[i].y += SPEED * -sinf(_snake[i].angle);
		if (_snake[i].x == _snake[i].toX && _snake[i].y == _snake[i].toY)
		{
			_snake[i].angle = getAngle(_snake[i].x, _snake[i].y, _snake[i - 1].x, _snake[i - 1].y);
		}
*/



		_snake[i].x += SPEED * cosf(_snake[i].angle);
		_snake[i].y += SPEED * -sinf(_snake[i].angle);
		_snake[i].angle = getAngle(_snake[i].x, _snake[i].y, _snake[i - 1].x, _snake[i - 1].y);
	}	
	// 이동
}
