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
	_x = 100;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, 80, 80);
	// 주인공

	score = 0;
	_isStart = true;
	_isDead = _isStuck = false; // 초기값
	_jumpCount = 2; // 점프가능 횟수
	_jumpPower = 0;
	_gravity = 0.3f;
	status = GROUND;


	for (int i = 0; i < 3; i++)
	{
		_ground[i] = RectMakeCenter(i*900, WINSIZEY / 2 +80,
			RND->getFromIntTo(400, 600),80);
	}
	_obstacle[0] = RectMake((2.0 / 3.0) * (WINSIZEX), RND->getFromIntTo(200, 300), 50, 50); // 기본
	_obstacle[1] = RectMake(WINSIZEX, RND->getFromIntTo(200, 300), 200, 50); // 넓쭉
	_obstacle[2] = RectMake((4.0 / 3.0) * WINSIZEX+50, RND->getFromIntTo(150, 250), 50, 150); // 넓쭉
	


	/*RECT _rc;
	RECT _obstacle[3]; // 장애물
	RECT _ground[3]; // 바닥*/


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

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // 재시작엔터
		if (score > highScore) highScore = score;
		if (!_isStart) _isStart = true;
		if (_isStart&&_isDead) this->init();
	}

	if (!_isDead && _isStart)
	{
		_y -= _jumpPower; _jumpPower -= _gravity; // 기본세팅
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
		{ // 점프
			if (_jumpCount > 0)
			{ // 점프카운트가 있어야
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
					&& (temp.right-temp.left)< (temp.bottom - temp.top)) //부딪힌 높이가 너비보다 클때
				{ // 왼쪽변에 충돌
					_x = _ground[i].left - 40;
				}
				else if (_rc.right > _ground[i].right && _rc.left < _ground[i].right
					&& (temp.right - temp.left) < (temp.bottom - temp.top)) //부딪힌 높이가 너비보다 클때
				{ // 오른쪽변 충돌
					_x = _ground[i].right + 40;
					_isStuck = true;
				}
				else if (_rc.bottom > _ground[i].top && _rc.top < _ground[i].top && _jumpPower>=0)
				{// 아래로 부딪힐때 착지
					_jumpPower = 0;
					_gravity = 0.0f;
					_y = WINSIZEY / 2;
					status = GROUND;
				}
				else if (_rc.bottom > _ground[i].bottom && _rc.top < _ground[i].bottom)
				{// 위로 부딪힐때 속도 0이상이면 없애기
					if (_jumpPower > 0)	_jumpPower = 0;
					_y = WINSIZEY / 2+160;
				}
			}
			if (IntersectRect(&temp, &_rc, &_obstacle[i]))
			{
				if (_rc.right > _obstacle[i].left && _rc.left < _obstacle[i].left
					&& (temp.right - temp.left) < (temp.bottom - temp.top)) //부딪힌 높이가 너비보다 클때
				{ // 왼쪽변에 충돌
					_x = _obstacle[i].left - 40;
					_isStuck = true;
				}
				else if (_rc.right > _obstacle[i].right && _rc.left < _obstacle[i].right
					&& (temp.right - temp.left) < (temp.bottom - temp.top)) //부딪힌 높이가 너비보다 클때
				{ // 오른쪽변 충돌
					_x = _obstacle[i].right + 40;
				}
				else if (_rc.bottom > _obstacle[i].top	&& _rc.top < _obstacle[i].top && _jumpPower>=0)
				{// 아래로 부딪힐때 착지
					if (_jumpPower < 0) _jumpPower = 0;
					_gravity = 0.0f;
					_y = _obstacle[i].top - 40;
					status = GROUND;
				}
				else if (_rc.bottom > _obstacle[i].bottom && _rc.top < _obstacle[i].bottom)
				{// 위로 부딪힐때 속도 0이상이면 없애기
					if (_jumpPower > 0)	_jumpPower = 0;
					_y = _obstacle[i].bottom+40;
				}
			}
		}
		_rc2 = RectMakeCenter(_x, _y + 1, 80, 80);//땅위에있나 판정용 RECT
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
		_rc2 = RectMakeCenter(_x+1, _y, 80, 80);//오른쪽에 있나 판정용 RECT
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
		{// 중점 아니면 이동
			if (_x < -40)
			{ // 왼쪽끝 죽음
				_isDead = true;
			}
			else
			{ // 제 위치 복귀
				if(status==GROUND) _x += 1;
			}
		}
		if (_y > WINSIZEY + 40)
		{ // 낙사
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

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================


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
		sprintf_s(str, "재시작하려면 ENTER");
		TextOut(backDC, WINSIZEX / 2 - 50, WINSIZEY / 2, str, strlen(str));
	}
	sprintf_s(str, "현재 점수 : %d", score/10);
	TextOut(backDC, WINSIZEX / 2 - 50, 50, str, strlen(str));
	sprintf_s(str, "최고 점수 : %d", highScore/10);
	TextOut(backDC, WINSIZEX / 2 - 50, 30, str, strlen(str));
	sprintf_s(str, "점프 : SPACE키");
	TextOut(backDC, WINSIZEX - 105, 30, str, strlen(str));
	sprintf_s(str, "수구리(땅에 있을때만) : ↓키");
	TextOut(backDC, WINSIZEX - 200, 50, str, strlen(str));
	sprintf_s(str, "종료 : ESC키");
	TextOut(backDC, WINSIZEX - 200, 70, str, strlen(str));

	//================= 아래도 건들지 마라 ==============================

	this->getBackBuffer()->render(hdc, 0, 0);
}
