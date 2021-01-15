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

	_timeCount = 0;
	_score = 0;
	_leftCount = 20;
	_isStand = _animationDown = false;
	_randNum = 13;
	_rotationCount = 0;

	for (int i = 0; i < 12; i++)
	{
		if (i/4==0) _target[i] = RectMakeCenter(150 + (WINSIZEX-100)/4 * i, 175, 50,50); // 0,1,2,3 멀
		else if (i/4==1) _target[i] = RectMakeCenter(150 + (WINSIZEX - 100) / 4 * (i-4), 390, 100, 120); // 4,5,6,7 중
		else _target[i] = RectMakeCenter(150 + (WINSIZEX - 100) / 4 * (i-8), WINSIZEY-125, 125, 150); // 8,9,10,11 가
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

	if (_animationDown)
	{
		_animation.top += 10;
	}
	if (_animation.top >= _animation.bottom) _animationDown = false;

	if (_isStand && _animation.top >= _target[_randNum].top)
	{
		_animation.top -= 20;
	}

	if (_leftCount > 0) // 사격횟수 살아있을때
	{
		_timeCount++; // 시간잼
		if (!_isStand && _timeCount >= 100) // 1초 기다려줌
		{
			_isStand = true;
			_timeCount = 0;
			_randNum = _rotation[_rotationCount] * 4 + rand() % 4;
			_rotationCount++;
			_animation = { _target[_randNum].left, _target[_randNum].bottom,
			_target[_randNum].right, _target[_randNum].bottom };
		}

		if (_isStand && _timeCount >= 100) // 1초 기다려줌
		{
			_isStand = false;
			_timeCount = 0;
			_leftCount--;
			_animationDown = true;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _isStand)
		{
			_leftCount--;
			_timeCount = 0;
			if (PtInRect(&_animation, _ptMouse) && _isStand)
			{
				_score++;
			}
			if(_isStand) _animationDown = true;
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
	
	Rectangle(backDC, 50, 50, WINSIZEX - 50, WINSIZEY -50); // 판
	
	MoveToEx(backDC, 50, 200, NULL);
	LineTo(backDC, WINSIZEX - 50, 200); //  구분 줄
	MoveToEx(backDC, 50, 450, NULL);
	LineTo(backDC, WINSIZEX - 50, 450); //  구분 줄

	Rectangle(backDC, _animation);

	char str[256];	
	sprintf_s(str, "남은 기회 : %d (시간내로 못쏴도 기회 날아감)", _leftCount);
	TextOut(backDC, WINSIZEX - 350, 20, str, strlen(str));
	sprintf_s(str, "맞춘 횟수 : %d", _score);
	TextOut(backDC, 50, 20, str, strlen(str));
	sprintf_s(str, "멀");
	TextOut(backDC, 20, 125, str, strlen(str));
	sprintf_s(str, "중");
	TextOut(backDC, 20, 325, str, strlen(str));
	sprintf_s(str, "가");
	TextOut(backDC, 20, WINSIZEY - 150, str, strlen(str));

	if (!_isStand && _leftCount > 0)
	{
		sprintf_s(str, "Ready? : %d", 10-_timeCount/10);
		TextOut(backDC, WINSIZEX/2-50, WINSIZEY/2, str, strlen(str));
	}
	else if (_isStand && _leftCount > 0)
	{
		sprintf_s(str, "제한시간 : %d", 10 - _timeCount / 10);
		TextOut(backDC, WINSIZEX / 2 - 40, WINSIZEY -50, str, strlen(str));
	}
	if (_leftCount == 0)
	{
		sprintf_s(str, "재시작하려면 ENTER");
		TextOut(backDC, WINSIZEX / 2 - 90, WINSIZEY / 2, str, strlen(str));
	}

	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
