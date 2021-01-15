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
		_bullet[i].speed = _speed;
		_bullet[i].radius = 20;
		_bullet[i].isFire = false;
		_bullet[i].gravity = 0;

		_track[i].speed = _speed; // 총알이랑 트랙 배열수 같게해서 겸사겸사 이용
		_track[i].radius = TRACKSIZE;
		_track[i].gravity = 0; // 얜 이즈파이어생략
	}


	trackSet(); // 초기 한 번 그려준다

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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.angle <= 3.04)
	{
		_cannon.angle += 0.04f;
		trackSet(); // 방향키 돌릴떄 함수발동
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.angle >= 0.08)
	{
		_cannon.angle -= 0.04f;
		trackSet(); // 방향키 돌릴떄 함수발동
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) bulletFire();

	//포신 끝점 (어제 덕호가 목에서 피나오게 설명하면서 돌아다니던 그것)
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;


	bulletMove();

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	EllipseMakeCenter(backDC, _cannon.center.x, _cannon.center.y, 100, 100);
	LineMake(backDC, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	for (int i = BULLETMAX-1; i >=0; i=i-1)
	{
		if (!_bullet[i].isFire) continue;
		EllipseMakeCenter(backDC, _bullet[i].x, _bullet[i].y, _bullet[i].radius * 2, _bullet[i].radius * 2);
	}


	for (int i = BULLETMAX-1; i >=0 ; i--)
	{
		EllipseMakeCenter(backDC, _track[i].x, _track[i].y, _track[i].radius * 2, _track[i].radius * 2);
	}  // 트랙은 이즈파이어 상관없음
	
	
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
		_bullet[i].gravity += 0.08;
		_bullet[i].x += cosf(_bullet[i].angle) * _speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _speed + _bullet[i].gravity;

		//화면 왼쪽으로 나가면
		if (_bullet[i].x - _bullet[i].radius < 0)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

		//화면 오른쪽으로 나가면
		if (_bullet[i].x + _bullet[i].radius > WINSIZEX)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

		//화면 위쪽으로 나가면
		if (_bullet[i].y - _bullet[i].radius < 0)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

		//화면 아래쪽으로 나가면
		if (_bullet[i].y + _bullet[i].radius > WINSIZEY)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

	}
}

void playGround::trackSet()
{
	_track[0].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x;
	_track[0].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
	_track[0].angle = _cannon.angle;	// 기준점으로 _track[0]

	float gravity = 0.08f;

	for (int i = 1; i < BULLETMAX; i++)
	{
		_track[i].x = _track[0].x + (5*i) * cosf(_track[0].angle) * _speed;
		// 속도는 cos(angle)*spd이므로 i에 대해서 적분하면 i*cos(angle)*spd
		// 적분상수 C는 기준점인 _track[0].x
		// 5주기마다라서 i대신 5*i를 넣음
		_track[i].y = _track[0].y + (5*i) * (-sinf(_track[0].angle) * _speed)+ (5*i)*(5*i)/2* gravity;
		// 속도는 -sin(angle)*spd + i*gravity이므로 i에 대해서 적분하면 -i*sin*spd + i^2/2*gravity
		// 적분상수 C는 기준점인 _track[0].y
		// 5주기마다라서 i대신 5*i를 넣음. (i^2는 25i^2)
		if (_track[i].y > WINSIZEY + TRACKSIZE) break;
	}
}
