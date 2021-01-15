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

	_cannon.angle = PI / 2;
	_cannon.cannon = 100;
	_cannon.radius = 100;
	_cannon.center.x = WINSIZEX / 2;
	_cannon.center.y = WINSIZEY;

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].speed = 5;
		_bullet[i].radius = 20;
		_bullet[i].isFire = false;
		_bullet[i].gravity = 0;
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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.angle <= 3.04) _cannon.angle += 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.angle >= 0.08) _cannon.angle -= 0.04f;
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) bulletFire();

	//포신 끝점 (어제 덕호가 목에서 피나오게 설명하면서 돌아다니던 그것)
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;


	bulletMove();

	collision();

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	EllipseMakeCenter(backDC, _cannon.center.x, _cannon.center.y, 100, 100);
	LineMake(backDC, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue;
		EllipseMakeCenter(backDC, _bullet[i].x, _bullet[i].y, _bullet[i].radius * 2, _bullet[i].radius * 2);
		
	}
	
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::bulletFire()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire) continue;

		_bullet[i].isFire = true;
		_bullet[i].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x;
		_bullet[i].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
		_bullet[i].angle = _cannon.angle;

		break;
	}
}


void playGround::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue;
		
		_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;

		//화면 왼쪽으로 나가면
		if (_bullet[i].x - _bullet[i].radius < 0)
		{
			_bullet[i].x = _bullet[i].radius;
			_bullet[i].angle = PI - _bullet[i].angle;
		}

		//화면 오른쪽으로 나가면
		if (_bullet[i].x + _bullet[i].radius > WINSIZEX)
		{
			_bullet[i].x = WINSIZEX - _bullet[i].radius;
			_bullet[i].angle = PI - _bullet[i].angle;
		}

		//화면 위쪽으로 나가면
		if (_bullet[i].y - _bullet[i].radius < 0)
		{
			_bullet[i].y = _bullet[i].radius;
			_bullet[i].angle = 2 * PI - _bullet[i].angle;
		}

		//화면 아래쪽으로 나가면
		if (_bullet[i].y + _bullet[i].radius > WINSIZEY)
		{
			_bullet[i].y = WINSIZEY - _bullet[i].radius;
			_bullet[i].angle = 2 * PI - _bullet[i].angle;
		}

	}
}

void playGround::collision()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		for (int j = i + 1; j < BULLETMAX; j++)
		{
			if (_bullet[i].radius * 2 < getDistance(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y)) continue;

			_bullet[i].angle = getAngle(_bullet[j].x, _bullet[j].y, _bullet[i].x, _bullet[i].y);
			_bullet[j].angle = getAngle(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y);
			// get앵글 서순 중요
		}
	}
}
