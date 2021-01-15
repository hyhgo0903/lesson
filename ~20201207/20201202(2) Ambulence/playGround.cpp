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

	srand(time(NULL));
	setImage();

	_ambul = RectMake(220 - 41, 550, 82, 156);

	_appearCount = _speed = _regenCount = _sideSpeed = _score = _loopX = _loopY = 0;
	_oil = 20.;

	for (int i = 0; i < 5; i++)
	{
		_taxi[i].appear = false;
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

	if (_oil <= 0 && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{//엔터로 재시작
		this->init();
	}

	if (_oil > 0)
	{
		_oil -= 0.005f;// 오일닳음
		if (_speed < 20) _speed += 0.05f; // 20까지 증가
		if (_regenCount < REGENTIME) _regenCount++; // 리젠카운트
		else taxiRegen(); // 리젠타임 됐으면 택시리젠

		for (int i = 0; i < 5; i++)
		{ // 택시 이동
			if (!_taxi[i].appear) continue; // 등장한것만
			_taxi[i].rc.top += _speed - _taxi[i].speed; // 내스피드-택시스피드 상대속도만큼 다가옴
			_taxi[i].rc.bottom = _taxi[i].rc.top + 155;
			if (_taxi[i].rc.top > WINSIZEY)
			{// 맵밖으로 넘어갔으면
				if (_score < 99) _score++;
				_taxi[i].appear = false; // 점수올리고 다시 쓸수있게 폴스
			}
		}

		if (_ambul.top > 550) // 제자리를 벗어났으면 제자리로 자기 속도만큼 간다.
		{
			_ambul.top -= _speed;
			_ambul.bottom = _ambul.top + 156;
		}

		if (_sideSpeed >= 0.2) // 사이드 스피드가 있으면 옮겨준다(측면추돌한 경우)
		{
			_ambul.left += _sideSpeed;
			_ambul.right = _ambul.left + 82;
			_sideSpeed -= 0.5f;
		}
		else if (_sideSpeed <= -0.2) // 사이드 스피드가 있으면 옮겨준다(측면추돌한 경우)
		{
			_ambul.left += _sideSpeed;
			_ambul.right = _ambul.left + 82;
			_sideSpeed += 0.5f;
		}

		if (_ambul.top <= 550) // 앰뷸이 제자리에 있다면 루프하는맵을 스피드만큼 옮겨줌
		{
			_loopY -= _speed;
		}		


		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sideSpeed < 0.3 && _sideSpeed >-0.3 && _speed > 0 && _ambul.left > 22)
		{ // 사이드스피드가 거의 없고 스피드가 있을때 + 왼쪽밖 못나갈떄 왼쪽을 누른상태면
			_ambul.left -= 5;
			_ambul.right = _ambul.left + 82;
		} // 사이드스피드가 거의 없고 스피드가 있을때 + 오른쪽밖 못나갈떄 왼쪽을 누른상태면
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sideSpeed < 0.3 && _sideSpeed>-0.3 && _speed > 0 && _ambul.right < 426)
		{
			_ambul.left += 5;
			_ambul.right = _ambul.left + 82;
		}


		collision();
		taxiTaxiCollision();
		gaugeAngle();
	}
	
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	_backgroundImg->loopRender(backDC, &RectMake(0, 0, 450, 1466), _loopX, _loopY); // 배경
	_ambulImg->render(backDC, _ambul.left, _ambul.top); // 앰뷸그림
	for (int i = 0; i < 5; i++)
	{ // 나타난것만 택시 그려줌
		if (!_taxi[i].appear) continue;
		_taxiImg->render(backDC, _taxi[i].rc.left, _taxi[i].rc.top);
	}
	_gauge->render(backDC, 470, 50); // 게이지

	HPEN pen = CreatePen(PS_DASHDOT, 1, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(backDC, pen);
	LineMake(backDC, 595, 180, 595 + 100 * cosf(_speedAngle), 180 - 100 * sinf(_speedAngle));
	LineMake(backDC, 595, 270, 595 + 40 * cosf(_oilAngle), 270 - 40 * sinf(_oilAngle));
	SelectObject(backDC, oldPen);
	DeleteObject(pen); // 게이지 바늘

	if (_oil <= 0)
	{ // 오일없으면(게임오버) 성의없어 보이는 엔터그림이 당신을 반긴다
		_restartImg->render(backDC, 100, WINSIZEY/2 - 100);
	}
	_number[_score / 10]->render(backDC, 490, 400); // 스코아
	_number[_score % 10]->render(backDC, 590, 400);

	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::setImage() // 이미지세팅
{
	_backgroundImg = IMAGEMANAGER->addImage("차로", "image/background.bmp", 450, 1466, false, RGB(255, 0, 255));
	_gauge = IMAGEMANAGER->addImage("게이지", "image/gauge.bmp", 262, 262, true, RGB(255, 0, 255));
	_taxiImg = IMAGEMANAGER->addImage("택시", "image/taxi.bmp", 87, 155, true, RGB(255, 0, 255));
	_ambulImg = IMAGEMANAGER->addImage("앰뷸", "image/ambul.bmp", 82, 156, true, RGB(255, 0, 255));
	_restartImg = IMAGEMANAGER->addImage("게임오버", "image/restart.bmp", 251, 201, false, RGB(0,0,0));

	for (int i = 0; i < 10; i++) // 숫자
	{
		char str[256];
		sprintf_s(str, "image/number%d.bmp", i);
		_number[i] = IMAGEMANAGER->addImage(str, str, 100, 100, true, RGB(255, 0, 255));
	}
}

void playGround::taxiRegen()
{
	_appearCount = 0;
	for (int i = 0; i < 5; i++)
	{ // 화면에 차 몇개 나와있는지 센다
		if (_taxi[i].appear) _appearCount++;
	}
	if (_appearCount < 3) // 3개넘으면 리젠안함
	{
		for (int i = 0; i < 5; i++)
		{
			if (_taxi[i].appear) continue; // 이즈파이어같은거
			_taxi[i].appear = true;
			_taxi[i].speed = 9 + rand() % 6; // 속도 9~14
			_randNum = (_randNum + 1 + rand() % 2 ) % 3; // 이렇게 하면 연달아 안뽑음(2였으면 3이나 4가 되어 3나머지는 0이나 1이 됨)
			switch (_randNum)
			{ // 왼쪽 중간 오른쪽 렉트생성
			case 0: _taxi[i].rc = RectMake(36, -155, 87, 155);
				break;
			case 1: _taxi[i].rc = RectMake(180, -155, 87, 155);
				break;
			case 2: _taxi[i].rc = RectMake(325, -155, 87, 155);
				break;
			}
			_regenCount = 0; // 만들었으면 카운트 내리고 브레이크
			break;
		}
	}
}

void playGround::collision()
{
	for (int i = 0; i < 5; i++)
	{
		if (!_taxi[i].appear) continue; // 이즈파이어같은거
		if (IntersectRect(&_temp, &_ambul, &_taxi[i].rc))
		{ // 부딪
			_oil-=2.; // 오일감소
			if (_temp.right - _temp.left <= _temp.bottom - _temp.top)
			{ // 폭이 더 작으면 옆에서 받은거
				_speed /= 3.0; // 감속
				if (_ambul.left < _taxi[i].rc.left) // 앰뷸이 왼쪽
				{
					_sideSpeed = -7.; // 옆속도 만들어줌
				}
				else
				{//앰뷸이 오른쪽
					_sideSpeed = 7.; // 옆속도 만들어줌
				}
				continue;
			}
			else
			{ // 위아래로 받은거
				_speed = -4.;
				_ambul.top = 551; // 밖으로 보내줘서 맵이동안하게 + 스피드 적용받게
				_ambul.bottom = _ambul.top + 156;
			}
		}
	}
}

void playGround::taxiTaxiCollision()
{
	for (int i = 0; i < 5; i++)
	{
		if (!_taxi[i].appear) continue;
		for (int j = i + 1; j < 5; j++)
		{
			if (!_taxi[j].appear) continue;
			if (IntersectRect(&_temp, &_taxi[i].rc, &_taxi[j].rc))
			{ // 택시 지들끼리 받을수도 있으니까
				if (_taxi[i].speed > _taxi[j].speed) // i가 더 빠른놈(뒤에서 받은놈)
				{
					_taxi[i].speed -= 7; // 빠른놈 성질을 좀 죽인다
					_taxi[i].rc.top = _taxi[j].rc.bottom + 1; // 안전거리 1
					_taxi[i].rc.bottom = _taxi[i].rc.top + 155;
				}
				else // j가 더 빠른놈(뒤에서 받은 놈)
				{
					_taxi[j].speed -= 7;
					_taxi[j].rc.top = _taxi[i].rc.bottom + 1;
					_taxi[j].rc.bottom = _taxi[j].rc.top + 155;
				}
			}
		}

	}
}

void playGround::gaugeAngle()
{ // 게이지각도 대충 계산
	if (_speed > 0)
	{
		_speedAngle = 7.0 / 6.0 * PI - PI*_speed/15.0;
	}
	else _speedAngle = 7.0 /6.0 * PI;
	_oilAngle = PI - PI / 6.0 - PI*(float)_oil / 30.0;
}


