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

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].isFire = false;
	}

	_regenCount = 0;
	_angle = PI / 2.0;

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
	_regenCount++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _angle < PI-0.025)
	{
		_angle += 0.05f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _angle > 0.025)
	{
		_angle -= 0.05f;
	}
	
	cannon();

	cannonMove();

	if (_regenCount >= 50 && !_isStand)
	{
		_isStand = true;
		_wind =0.1*(rand() % 11 - 5);
		_target = RectMakeCenter(RND->getFromIntTo(200, WINSIZEX - 200), RND->getFromIntTo(WINSIZEY/2, WINSIZEY - 200), 100, 100);
	}
	if (_regenCount >= 150)
	{
		_isStand = false;
		_target = RectMakeCenter(0, 0, 0, 0);
		_regenCount = 0;
	}

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================


	Rectangle(backDC, _target);

	EllipseMakeCenter(backDC, WINSIZEX / 2, WINSIZEY, 100, 100);
	for (int i = 0; i < BULLETMAX; i++)
	{
		Ellipse(backDC, _bullet[i].rc);
	}

	MoveToEx(backDC, WINSIZEX / 2, WINSIZEY, NULL);
	LineTo(backDC, WINSIZEX / 2 + 70.0*cosf(_angle), WINSIZEY+ 70.0*-sinf(_angle));

	char str[256];
	if (_wind > 0)
	{
		sprintf_s(str, "바람세기(왼쪽으로) : %.1f", _wind);
		TextOut(backDC, 210, 10, str, strlen(str));
	}
	else if (_wind < 0)
	{
		sprintf_s(str, "바람세기(오른쪽으로) : %.1f", -_wind);
		TextOut(backDC, WINSIZEX-400, 10, str, strlen(str));
	}
	else
	{
		sprintf_s(str, "무풍");
		TextOut(backDC, WINSIZEX/2, 10, str, strlen(str));
	}
	sprintf_s(str, "스코아 : %d", _score/100);
	TextOut(backDC, WINSIZEX / 2-50, 30, str, strlen(str));



	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::cannon()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire) continue; // 안쏘는 중인것만 쏠거야
		_bullet[i].x = WINSIZEX / 2 + 70.0 * cosf(_angle);
		_bullet[i].y = WINSIZEY + 70.0 * -sinf(_angle);
		_bullet[i].spdX = _speed * cosf(_angle);
		_bullet[i].spdY = _speed * -sinf(_angle);
		_bullet[i].isFire = true;
		break; // 쐈으면 브레이크
	}
}

void playGround::cannonMove()
{ 
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue; // 쏘는중인것만 판단할거야
		if (_bullet[i].y <-BULLETSIZE || _bullet[i].y > WINSIZEY+ BULLETSIZE) _bullet[i].isFire = false;
		if ((_bullet[i].x < BULLETSIZE || _bullet[i].x > WINSIZEX - BULLETSIZE )
			&& _bullet[i].spdX!=0) _bullet[i].spdX *= -0.8;
		{
			_bullet[i].x += _bullet[i].spdX;
			_bullet[i].spdX -= _wind;
			_bullet[i].y += _bullet[i].spdY;
			_bullet[i].spdY += _gravity;
			_bullet[i].rc = RectMakeCenter(_bullet[i].x, _bullet[i].y, BULLETSIZE, BULLETSIZE);
			if (IntersectRect(&temp, &_bullet[i].rc, &_target)) _score++;
		}// 아니면 스피드대로 이동해준다
	}
}