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

	_day = new image;
	_day->init("image/day500600.bmp", 500, 600, false, RGB(0, 0, 0));

	_night = new image;
	_night->init("image/night500600.bmp", 500, 600, false, RGB(0, 0, 0));

	_background = _day;

	_count = _score = 0;
	_isNight = _isDead = false;

	_bird.x = WINSIZEX / 2 - 100;
	_bird.y = WINSIZEY / 2;
	_bird.jumpPower = 0;
	_bird.gravity = 0.1;
	_alki = new image;
	_alki->init("image/alki.bmp", 100, 100, true, RGB(255, 0, 255));
	_alki2 = new image;
	_alki2->init("image/alki2.bmp", 100, 100, true, RGB(255, 0, 255));
	_restart = new image;
	_restart->init("image/restart.bmp", 251, 201, false, RGB(0, 0, 0));

	char str[256];
	for (int i = 0; i < 10; i++)
	{
		_number[i] = new image;
		sprintf_s(str, "image/number%d.bmp", i);
		_number[i]->init(str, 100, 100, true, RGB(255, 0, 255));
	}

	_uppipe = new image;
	_uppipe->init("image/uppipe100600.bmp", 100, 600, true, RGB(255, 0, 255));
	_downpipe = new image;
	_downpipe->init("image/downpipe100600.bmp", 100, 600, true, RGB(255, 0, 255));

	_upPipeWitch = rand() % 300 - 600;
	_upPipeRc[0] = RectMake(WINSIZEX, _upPipeWitch, 100, 600); // -600~-299이므로 화면엔 0~300높이
	_downPipeRc[0] = RectMake(WINSIZEX, _upPipeWitch + 900, 100, 600); // 위랑 300간격두고 이격
	_upPipeWitch = rand() % 300 - 600;
	_upPipeRc[1] = RectMake(WINSIZEX+300, _upPipeWitch, 100, 600);
	_downPipeRc[1] = RectMake(WINSIZEX+300, _upPipeWitch + 900, 100, 600);

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
	if (_isDead && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // 죽었을때 엔터로 초기화
		this->init();
	}

	if (!_isDead)
	{
		_count++;

		if (_count > 300)
		{ // 수업시간에 구현하신 낮밤
			_isNight == false ? _isNight = true : _isNight = false;

			_count = 0;
		}

		if (!_isNight) _background = _day;
		else _background = _night;



		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{ // 점프
			_bird.jumpPower = 5;
		}

		_bird.y -= _bird.jumpPower;		_bird.jumpPower -= _bird.gravity;
		// y를 이동해줌 + 중력적용

		_bird.rc = RectMakeCenter(_bird.x, _bird.y, 77, 57);
		_bird.rc2 = RectMakeCenter(_bird.x, _bird.y, 57, 77);
		// 원에 가깝도록(원사각충돌안쓰고) 사각형 두개를 이용
		// 원에 가깝도록(원사각충돌안쓰고) 사각형 두개를 이용

		for (int i = 0; i < 2; i++)
		{ // 기둥 리젠
			_upPipeRc[i].left -= 3; _upPipeRc[i].right -= 3;
			_downPipeRc[i].left -= 3; _downPipeRc[i].right -= 3;
			if (_upPipeRc[i].right < 0)
			{
				_score++;
				if (_score > 99) _score -= 100; // 혹시 백넘으면 0으로 초기화
				_upPipeWitch = rand() % 300 - 600; // -600~-299이므로 화면엔 0~300높이
				_upPipeRc[i] = RectMake(WINSIZEX, _upPipeWitch, 100, 600);
				_downPipeRc[i] = RectMake(WINSIZEX, _upPipeWitch + 900, 100, 600); // 위랑300이격
			}
		}
		
		if (_bird.rc.top > WINSIZEY) _isDead = true;
		for (int i = 0; i < 2; i++)
		{ // 부딪죽음
			if (IntersectRect(&_temp, &_upPipeRc[i], &_bird.rc)) _isDead = true;
			if (IntersectRect(&_temp, &_downPipeRc[i], &_bird.rc)) _isDead = true;
			if (IntersectRect(&_temp, &_upPipeRc[i], &_bird.rc2)) _isDead = true;
			if (IntersectRect(&_temp, &_downPipeRc[i], &_bird.rc2)) _isDead = true;
		}
	}
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	_background->render(backDC, 0, 0);
	if (_bird.jumpPower > 0)
	{ // 위로갈떄 알키가 웃음
		_alki->render(backDC, _bird.rc.left-12, _bird.rc.top-20);	}
	else
	{ // 아니면 무표정
		_alki2->render(backDC, _bird.rc.left - 12, _bird.rc.top - 20);	}

	for (int i = 0; i < 2; i++)
	{		_uppipe->render(backDC, _upPipeRc[i].left, _upPipeRc[i].top);
		_downpipe->render(backDC, _downPipeRc[i].left, _downPipeRc[i].top);	}
	// 십의자리는 10나눈 몫 1의 자리는 10나눈 나머지. 100의 자리는 그럴거같지 않아서 안만듦
	_number[_score / 10]->render(backDC, WINSIZEX - 200, 20);
	_number[_score % 10]->render(backDC, WINSIZEX - 100, 20);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{ // 충돌판정
		Rectangle(backDC, _bird.rc);		Rectangle(backDC, _bird.rc2);
	}

	if (_isDead)
	{ // 겜오버
		_restart->render(backDC, WINSIZEX/2 - 125, WINSIZEY/2 -100);
	}
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
