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

	int _점수 = _combo = 0;
	
	for (int i = 0; i < BARMAX; i++)
	{
		_bar[i].isOnScreen=false;
		_bar[i].isRight = false;
	}


	for (int i = 0; i < 7; i++)
	{
		_refereeRect[i] = RectMake(50 + 75*i, WINSIZEY - 150, 75, 125);
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

	if (KEYMANAGER->isOnceKeyDown('S')) pressS();
	if (KEYMANAGER->isOnceKeyDown('D')) pressD();
	if (KEYMANAGER->isOnceKeyDown('F')) pressF();
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) pressSpace();
	if (KEYMANAGER->isOnceKeyDown('J')) pressJ();
	if (KEYMANAGER->isOnceKeyDown('K')) pressK();
	if (KEYMANAGER->isOnceKeyDown('L')) pressL();

	_musicCount++;
	


	// =========== 일정주기 랜덤으로 할거면 이걸로========

	if (_musicCount >= 15)
	{
		MakeRandom();
		_musicCount = 0;
	}
	
	// ============ 여기에 노트를 입력하세요 ==========
	
	/*
	if (_musicCount == 20)
	{
		MakeS();
		MakeL();
	}
	if (_musicCount == 40)
	{
		MakeD();
		MakeK();
	}
	if (_musicCount == 60)
	{
		MakeF();
		MakeJ();
	}
	if (_musicCount == 80)
	{
		MakeSpace();
	}*/




	// =========== 여기에 노트를 입력하세요 =================

	for (int i = 0; i < BARMAX; i++)
	{
		if (!_bar[i].isOnScreen) continue;
		_bar[i].rc.bottom += 8; _bar[i].rc.top += 8;
		if (_bar[i].rc.top > WINSIZEY)
		{
			_bar[i].isOnScreen = false;
			if (!_bar[i].isRight)
			{
				if(_score > 0) _score--;
				_combo = 0;
			}
		}

	}

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	LineMake(backDC, 50 , WINSIZEY-100, 50 + 75 * 7, WINSIZEY - 100);
	LineMake(backDC, 50, WINSIZEY - 75, 50 + 75 * 7, WINSIZEY - 75);
	for(int i = 0; i < 8; i++)
	{
		LineMake(backDC, 50+75*i, 0, 50 + 75 * i, WINSIZEY);
	}

	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen && !_bar[i].isRight) Rectangle(backDC, _bar[i].rc);
		else if (_bar[i].isOnScreen && _bar[i].isRight)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
			HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
			Rectangle(backDC, _bar[i].rc);
			SelectObject(backDC, oldbrush);
			DeleteObject(brush);
		}
	}
	
	char str[256];
	sprintf_s(str, "S");
	TextOut(backDC, 85, WINSIZEY - 95, str, strlen(str));
	sprintf_s(str, "D");
	TextOut(backDC, 160, WINSIZEY - 95, str, strlen(str));
	sprintf_s(str, "F");
	TextOut(backDC, 235, WINSIZEY - 95, str, strlen(str));
	sprintf_s(str, "SPACE");
	TextOut(backDC, 295, WINSIZEY - 95, str, strlen(str));
	sprintf_s(str, "J");
	TextOut(backDC, 385, WINSIZEY - 95, str, strlen(str));
	sprintf_s(str, "K");
	TextOut(backDC, 460, WINSIZEY - 95, str, strlen(str));
	sprintf_s(str, "L");
	TextOut(backDC, 535, WINSIZEY - 95, str, strlen(str));
	sprintf_s(str, "점수 : %d", _score);
	TextOut(backDC, 610, 95, str, strlen(str));
	sprintf_s(str, "콤보 : %d", _combo);
	TextOut(backDC, 610, 110, str, strlen(str));



	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::pressS()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (IntersectRect(&temp, &_bar[i].rc, &_refereeRect[0]) && !_bar[i].isRight)
		{
			_bar[i].isRight = true;
			_score++;
			_combo++;
		}
	}
}

void playGround::pressD()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (IntersectRect(&temp, &_bar[i].rc, &_refereeRect[1]) && !_bar[i].isRight)
		{
			_bar[i].isRight = true;
			_score++;
			_combo++;
		}
	}
}

void playGround::pressF()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (IntersectRect(&temp, &_bar[i].rc, &_refereeRect[2]) && !_bar[i].isRight)
		{
			_bar[i].isRight = true;
			_score++;
			_combo++;
		}
	}
}

void playGround::pressSpace()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (IntersectRect(&temp, &_bar[i].rc, &_refereeRect[3]) && !_bar[i].isRight)
		{
			_bar[i].isRight = true;
			_score++;
			_combo++;
		}
	}
}

void playGround::pressJ()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (IntersectRect(&temp, &_bar[i].rc, &_refereeRect[4]) && !_bar[i].isRight)
		{
			_bar[i].isRight = true;
			_score++;
			_combo++;
		}
	}
}

void playGround::pressK()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (IntersectRect(&temp, &_bar[i].rc, &_refereeRect[5]) && !_bar[i].isRight)
		{
			_bar[i].isRight = true;
			_score++;
			_combo++;
		}
	}
}

void playGround::pressL()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (IntersectRect(&temp, &_bar[i].rc, &_refereeRect[6]) && !_bar[i].isRight)
		{
			_bar[i].isRight = true;
			_score++;
			_combo++;
		}
	}
}

void playGround::MakeS()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = 0;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}

void playGround::MakeD()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = 1;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}

void playGround::MakeF()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = 2;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}

void playGround::MakeSpace()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = 3;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}

void playGround::MakeJ()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = 4;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}

void playGround::MakeK()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = 5;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}

void playGround::MakeL()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = 6;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}

void playGround::MakeRandom()
{
	for (int i = 0; i < BARMAX; i++)
	{
		if (_bar[i].isOnScreen) continue;
		_bar[i].status = rand() % 7;
		_bar[i].rc = RectMake(50 + 75 * _bar[i].status, -10, 75, 10);
		_bar[i].isRight = false;
		_bar[i].isOnScreen = true;
		break;
	}
}
