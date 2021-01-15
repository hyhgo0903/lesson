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

	_bowlimg = new image;
	_bowlimg->init("image/bowl.bmp", 30, 20, true, RGB(255,0,255));

	_background = new image;
	_background->init("image/background.bmp", 800, 350);
	_shooterCenter = new image;
	_shooterCenter->init("image/shootercenter.bmp", 57, 79, true, RGB(255, 0, 255));
	_shooterLeft = new image;
	_shooterLeft->init("image/shooterleft.bmp", 63, 78, true, RGB(255, 0, 255));
	_shooterRight = new image;
	_shooterRight->init("image/shooterright.bmp", 63, 78, true, RGB(255, 0, 255));
	_targetImg = new image;
	_targetImg->init("image/target.bmp", 35, 30, true, RGB(255, 0, 255));

	_timeUp = new image;
	_timeUp->init("image/timeup.bmp", 221, 210, true, RGB(255, 0, 255));

	_effect[0] = RectMake(WINSIZEX, 0, 0, 0);


	char str[256];
	for (int i = 0; i < 10; i++)
	{
		_number[i] = new image;
		sprintf_s(str, "image/number%d.bmp", i);
		_number[i]->init(str, 100, 100, true, RGB(255, 0, 255));
	}


	_shooterState = CENTER;
	_isEnd = false;

	_reloadCount = RELOADCOUNT;
	_regenTimer = _score = _leftChaseCount = _rightChaseCount = _gameCount = 0;

	for (int i = 0; i < BOWLMAX; i++)
	{
		_bowl[i].isFire = false;
		_bowl[i].rc = { 0,0,0,0 };
		_bowl[i].xSpd = 0;
		_bowl[i].ySpd = 0;
	}

	_leftTarget = RectMakeCenter(WINSIZEX / 2 - 45, WINSIZEY / 2-20, 35, 30);
	_rightTarget = RectMakeCenter(WINSIZEX / 2 + 45, WINSIZEY / 2-20, 35, 30);


	srand(time(NULL));


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


	if (!_isEnd)
	{
		if (_reloadCount < RELOADCOUNT) _reloadCount++; // 맞추면 바로 장전되는 재장전 카운트
		if (_standCount < 50) _standCount++;
		if (_standCount == 50) _shooterState = CENTER; // 쏜후 제자리로 돌아옴

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _reloadCount== RELOADCOUNT) left();
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _reloadCount == RELOADCOUNT) right();

		if (_regenTimer < REGENTIME) _regenTimer++; // 리젠카운트
		if (_regenTimer == REGENTIME) bowlRefill();
		bowlMove();

		if (_reloadCount != RELOADCOUNT)
		{
			_reloadRc = { (WINSIZEX - 80) / 2, WINSIZEY - 69 , (WINSIZEX - 57) / 2 + _reloadCount,WINSIZEY - 65 };
		}

		bowlSpot();

		_gameCount++;
		if (_gameCount > 2000)
		{
			_isEnd = true;
		}

		effect();
	}
	if (_isEnd && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		this->init();
	}


}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	_background->render(backDC, 0, 0);
	_targetImg->render(backDC, _leftTarget.left, _leftTarget.top);
	_targetImg->render(backDC, _rightTarget.left, _rightTarget.top);

	_number[_score / 10]->render(backDC, 0, 0);
	_number[_score % 10]->render(backDC, 100, 0);

	switch (_shooterState)
	{
	case CENTER:
		_shooterCenter->render(backDC, (WINSIZEX-57)/2, WINSIZEY-79);
		break;
	case LEFT:
		_shooterLeft->render(backDC, (WINSIZEX - 63) / 2, WINSIZEY - 78);
		break;
	case RIGHT:
		_shooterRight->render(backDC, (WINSIZEX - 63) / 2, WINSIZEY - 78);
		break;
	}

	for (int i = 0; i < BOWLMAX; i++)
	{
		if (!_bowl[i].isFire) continue;
		_bowlimg->render(backDC, _bowl[i].rc.left, _bowl[i].rc.top);
	}

	if (_reloadCount != RELOADCOUNT)
	{
		HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));
		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _reloadRc);
		SelectObject(backDC, oldbrush);
		DeleteObject(brush);
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(backDC, _leftTarget);
		Rectangle(backDC, _rightTarget);
		for (int i = 0; i < BOWLMAX; i++)
		{
			Rectangle(backDC, _bowl[i].rc);
		}

	}


	
	HBRUSH brush = CreateSolidBrush(RGB(255, 127, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
	for (int i = 0; i < 8; i++)
	{
		Ellipse(backDC, _effect[i]);
	}
	SelectObject(backDC, oldbrush);
	DeleteObject(brush);

	if (_isEnd)
	{
		_timeUp->render(backDC, WINSIZEX / 2 - 110, WINSIZEY / 2 - 105);
	}

	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::left()
{
	_reloadCount = 0;
	_shooterState = LEFT;
	_standCount = 0;
	for (int i = 0; i < BOWLMAX; i++)
	{
		if (IntersectRect(&_temp, &_bowl[i].rc, &_leftTarget) && _bowl[i].isFire)
		{
			_bowl[i].isFire = false;
			_reloadCount = RELOADCOUNT;
			if (_score < 99) _score++;
			for (int j = 0; j < 8; j++)
			{
				_effect[j] = RectMakeCenter((_bowl[i].rc.left + _bowl[i].rc.right) / 2,
					(_bowl[i].rc.top + _bowl[i].rc.bottom) / 2, 6, 6);
			}

		}
	}
}

void playGround::right()
{
	_reloadCount = 0;
	_shooterState = RIGHT;
	_standCount = 0;
	for (int i = 0; i < BOWLMAX; i++)
	{
		if (IntersectRect(&_temp, &_bowl[i].rc, &_rightTarget) && _bowl[i].isFire)
		{
			_bowl[i].isFire = false;
			_reloadCount = RELOADCOUNT;
			if (_score < 99) _score++;
			for (int j = 0; j < 8; j++)
			{
				_effect[j] = RectMakeCenter((_bowl[i].rc.left+ _bowl[i].rc.right)/2,
					(_bowl[i].rc.top + _bowl[i].rc.bottom) / 2, 6, 6);
			}
		}
	}
}

void playGround::bowlRefill()
{
	_regenTimer = 0;
	for (int i = 0; i < BOWLMAX; i++)
	{
		if (_bowl[i].isFire) continue; // 안쏘는 중인것만			
		_randNum = rand() % 5;
		switch (_randNum)
		{
		case 0: // 왼쪽(40%)
		case 1:
			_bowl[i].rc = RectMake(48, 265, 30, 20);
			_bowl[i].xSpd = 5 + rand() % 3;
			_bowl[i].ySpd = -7 - rand() % 3;
			_bowl[i].gravity = 0.2f;
			_bowl[i].isFire = true;
			break;
		case 2: // 오른쪽
		case 3:
		case 4:
			_bowl[i].rc = RectMake(757, 270, 30, 20);
			_bowl[i].xSpd = -5 - rand() % 3;
			_bowl[i].ySpd = -7 - rand() % 3;
			_bowl[i].gravity = 0.2f;
			_bowl[i].isFire = true;
		}
		break;
	}
}

void playGround::bowlMove()
{ // 자기 속도에 맞게 이동하고 중력도 적용됨
	for (int i = 0; i < BOWLMAX; i++)
	{
		if (!_bowl[i].isFire) continue;
		_bowl[i].rc.left += _bowl[i].xSpd; _bowl[i].rc.right = _bowl[i].rc.left+30;
		_bowl[i].rc.top += _bowl[i].ySpd; _bowl[i].rc.bottom = _bowl[i].rc.top +20;
		_bowl[i].ySpd += _bowl[i].gravity;
		if (_bowl[i].rc.top > 300) _bowl[i].isFire = false;
	}
}

void playGround::bowlSpot()
{
	_leftChaseCount = 0; _rightChaseCount = 0;
	for (int i = 0; i < BOWLMAX; i++)
	{
		if (_bowl[i].isFire && _bowl[i].xSpd > 0 
			&& _leftTarget.right - _bowl[i].rc.left > 0)
		{
			_leftChaseCount++;
		}
		if (_bowl[i].isFire && _bowl[i].xSpd < 0 
			&& _bowl[i].rc.right - _rightTarget.left > 0)
		{
			_rightChaseCount++;
		}
	}


	if (_leftChaseCount == 0) // 왼쪽에서 오는게 없다면 옆이랑 같이 움직
	{
		_leftTarget.top = _rightTarget.top;
		_leftTarget.bottom = _rightTarget.top + 30;
	}
	else
	{// 왼쪽에서 오는게 있다면 탐색을 한다
		_min = WINSIZEX;
		for (int i = 0; i < BOWLMAX; i++)
		{
			if (_bowl[i].isFire && _bowl[i].xSpd > 0 &&
				_leftTarget.right - _bowl[i].rc.left < _min && _leftTarget.right - _bowl[i].rc.left>-25)
			{
				_min = _leftTarget.right - _bowl[i].rc.left;
				_tempI = i; // 목표
			}
		}
		_leftTarget.top = _bowl[_tempI].rc.top-2;
		_leftTarget.bottom = _leftTarget.top + 30;
	}


	if (_rightChaseCount == 0) // 오른쪽에서 오는게 없으면 옆이랑 같이 움직
	{
		_rightTarget.top = _leftTarget.top;
		_rightTarget.bottom = _rightTarget.top + 30;
	}
	else
	{// 오른쪽에서 오는게 있다면 탐색을 한다
		_min = WINSIZEX;
		for (int i = 0; i < BOWLMAX; i++)
		{
			if (_bowl[i].isFire && _bowl[i].xSpd < 0 &&
				_bowl[i].rc.right - _rightTarget.left < _min && _bowl[i].rc.right - _rightTarget.left > -25)
			{
				_min = _bowl[i].rc.right - _rightTarget.left;
				_tempI = i; // 목표
			}
		}
		_rightTarget.top = _bowl[_tempI].rc.top-2;
		_rightTarget.bottom = _rightTarget.top + 30;
	}
}

void playGround::effect()
{
	if (_effect[0].left < WINSIZEX)
	{
		OffsetRect(&_effect[0], 14, 0);
		OffsetRect(&_effect[1], 0, 14);
		OffsetRect(&_effect[2], -14, 0);
		OffsetRect(&_effect[3], 0, -14);
		OffsetRect(&_effect[4], 10, 10);
		OffsetRect(&_effect[5], 10, -10);
		OffsetRect(&_effect[6], -10, 10);
		OffsetRect(&_effect[7], -10, -10);
	}
}
