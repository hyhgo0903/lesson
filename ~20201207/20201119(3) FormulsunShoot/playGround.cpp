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
	tar.rc = { 0,0,0,0 };
	_timeCount = 0;
	_score = 0;
	_leftCount = 20;
	_isStand = _animation = false;
	_randNum = 0;
	_gravity = 0.4f;
	_direction = 1;
	
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
	OffsetRect(&_effect[0], 28, 0);
	OffsetRect(&_effect[1], 0, 28);
	OffsetRect(&_effect[2], 20, 20);
	OffsetRect(&_effect[3], -28, 0);
	OffsetRect(&_effect[4], -20, -20);
	OffsetRect(&_effect[5], 0, -28);
	OffsetRect(&_effect[6], 20, -20);
	OffsetRect(&_effect[7], -20, 20);
	
	if (_leftCount > 0) // 사격횟수 살아있을때
	{
		_timeCount++; // 시간잼
		OffsetRect(&tar.rc , tar.x, -tar.y);
		tar.y -= _gravity;
		if (!_isStand && _timeCount >= 100) // 1초 기다려줌
		{
			_isStand = true;
			_timeCount = 0;
			_randNum = RND->getFromIntTo(100, 300); // 높이
			if (_direction > 0 ) tar.rc = {-50,_randNum,0,_randNum+50};
			else tar.rc = { WINSIZEX,_randNum,WINSIZEX+50,_randNum + 50 };
			_randNum = RND->getFromIntTo(8, 16);  // x속도
			tar.x = (float)_randNum * _direction;
			_randNum = RND->getFromIntTo(8, 12);  // y속도
			tar.y = (float)_randNum;

			_direction *= -1;
		}

		if (_isStand && tar.rc.top > WINSIZEY)
		{
			_isStand = false;
			_timeCount = 0;
			_leftCount--;
			if (_leftCount == 0 & _highScore < _score) _highScore = _score;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _isStand)
		{
			_leftCount--;
			_timeCount = 0;
			if (PtInRect(&tar.rc, _ptMouse) && _isStand)
			{
				_animation = true;
				for(int i = 0; i < 8; i++)
				{
					_effect[i] = { tar.rc.left+15,tar.rc.top+15,tar.rc.right-15,tar.rc.bottom-15 };
				}
				_score++;
				tar.rc = { 0,0,0,0 };
			}

			if (_leftCount == 0 & _highScore < _score) _highScore = _score;
			_isStand = false;
		}
	}
	if (_leftCount == 0 && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // 재시작
		this->init();
	}

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	if (_leftCount > 0) { Rectangle(backDC, tar.rc); }
	for (int i = 0; i < 8; i++)
	{
		Rectangle(backDC,_effect[i]);
	}

	char str[256];	
	sprintf_s(str, "남은 기회 : %d (못쏴도 기회 날아감)", _leftCount);
	TextOut(backDC, WINSIZEX - 300, 20, str, strlen(str));
	if (_leftCount > 0) {
		sprintf_s(str, "최고 기록 : %d", _highScore);
		TextOut(backDC, 50, 20, str, strlen(str));
		sprintf_s(str, "맞춘 횟수 : %d", _score);
		TextOut(backDC, 50, 40, str, strlen(str));
	}
	
	if (!_isStand && _leftCount > 0)
	{
		sprintf_s(str, "Ready? : %d", 10-_timeCount/10);
		TextOut(backDC, WINSIZEX/2-50, WINSIZEY/2, str, strlen(str));
	}
	if (_leftCount == 0)
	{
		sprintf_s(str, "최종 기록 : %d", _score);
		TextOut(backDC, WINSIZEX / 2 - 60, WINSIZEY / 2 - 40, str, strlen(str));
		sprintf_s(str, "(최고 기록 : %d)", _highScore);
		TextOut(backDC, WINSIZEX / 2 - 64, WINSIZEY / 2 - 20, str, strlen(str));
		sprintf_s(str, "재시작하려면 ENTER");
		TextOut(backDC, WINSIZEX / 2 - 90, WINSIZEY / 2, str, strlen(str));
	}

	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
