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

	_background = IMAGEMANAGER->addImage("배경", "image/background.bmp", 922, 630, false, RGB(255, 0, 255));
	_sonicImg = IMAGEMANAGER->addFrameImage("소닉", "image/sonic.bmp", 1100, 1000, 11, 10, true, RGB(255, 0, 255));
	// X 인덱스 는 0~10 Y는 0~9

	_isGapEum = _onGround = _isHang = false; // 헤더참조
	_sonicRc = RectMake(50, 300, SONICWIDTH, SONICHEIGHT); // 소닉
	
	_object[0] = { 211, 357, 584, 630 }; // 비주얼창
	_object[1] = { 672, 278, 922, 630 }; // 속성창

	_object[2] = { 0, 129, 180, 160 }; // 왼쪽 바
	_object[3] = { 827, 129, 922, 161 }; // 오른쪽 바
	_object[4] = { 319, 60, 581, 90 }; // 가운데 바

	_object[5] = { 0, 590, 922, 630 }; // 밑에 바

	for (int i = 0; i < 6; i++)
	{
		_objectIsNotCollide[i] = false;
	}

	_sonicImg->setFrameY(0);

	_count = _index = 0;

	_direction = RIGHT_JUMP;

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

	rectMove(); 	keyInput(); 	collision(); 	objectRegen(); // 각종함수

	// 점프중이나 매달린상태가 아니면 점프체크
	if (_direction != LEFT_JUMP && _direction != RIGHT_JUMP 
		&& _direction != LEFT_HANG && _direction != RIGHT_HANG) jumpingCheck();

	// 매달린상태면 매달렸는지 체크
	if (_direction == LEFT_HANG || _direction == RIGHT_HANG) hangingCheck();

	if (_count % 10 == 0)
	{
		animation();
		if (_count >= 100) _count = 0;	
	}


	_count++;

	if (_attackReturn < 30) _attackReturn++; // 30될때까지 공격쿨돌음
	else // 30이 되었을때 공격중이면 복귀해줌
	{
		if (_direction == RIGHT_ATTACK)
		{
			_direction = RIGHT_IDLE;			_index = 0;
			// 자리 바꿀때마다 인덱스값 부여해줌(이블린 방지용..)
		}
		else if (_direction == LEFT_ATTACK)
		{
			_direction = LEFT_IDLE;			_index = 10;
		}
	}
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	_background->render(backDC); // 배경
	_sonicImg->frameRender(backDC, _sonicRc.left - 16, _sonicRc.top -10); // 소닉

	if (KEYMANAGER->isToggleKey(VK_TAB)) // 탭누르면 사각형으로 보이는거
	{		
		for (int i = 0; i < 6; i++)
		{
			Rectangle(backDC, _object[i]);			
		}
		Rectangle(backDC, _sonicRc);
	}

	switch (_direction) // 상태 표시
	{
	case LEFT_RUN:		sprintf_s(str, "LEFT  _RUN");				break;
	case RIGHT_RUN:		sprintf_s(str, "RIGHT_RUN");				break;
	case LEFT_HANG:		if (_isGapEum)	sprintf_s(str, "LEFT  _HANG (완전히 붙잡음)");
						else sprintf_s(str, "LEFT  _HANG (미끌림)");	break;
	case RIGHT_HANG:	if (_isGapEum)sprintf_s(str, "RIGHT_HANG (완전히 붙잡음)");
						else sprintf_s(str, "RIGHT_HANG (미끌림)");	break;
	case LEFT_IDLE:		sprintf_s(str, "LEFT  _IDLE");				break;
	case RIGHT_IDLE:	sprintf_s(str, "RIGHT_IDLE");				break;
	case LEFT_ATTACK:	sprintf_s(str, "LEFT  _ATTACK");			break;
	case RIGHT_ATTACK:	sprintf_s(str, "RIGHT_ATTACK");				break;
	case LEFT_JUMP:		sprintf_s(str, "LEFT  _JUMP");				break;
	case RIGHT_JUMP:	sprintf_s(str, "RIGHT_JUMP");				break;
	}
	TextOut(backDC, 87, 603, str, strlen(str));


	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::rectMove() // 렉트가 중력받고 내려가는거
{
	if (_direction == LEFT_JUMP || _direction == RIGHT_JUMP)
	{
		_sonicRc.top -= _jumpPower;
		_sonicRc.bottom = _sonicRc.top + SONICHEIGHT;
		_jumpPower -= 0.25f;
	}
	else if (_direction == LEFT_HANG || _direction == RIGHT_HANG)
	{ // 완전히 붙잡았으면 안내려가고 매달렸으면 천천히 낙하
		_sonicRc.top -= _jumpPower;
		_sonicRc.bottom = _sonicRc.top + SONICHEIGHT;
		if (!_isGapEum) _jumpPower -= 0.05f;
	}
}

void playGround::keyInput() // 키입력 모음
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sonicRc.left > 0)
	{ // 화면 안에서 왼쪽누른 상태
		_sonicRc.left -= 5; // 이동시키고
		_sonicRc.right = _sonicRc.left + SONICWIDTH;
		if (_direction == LEFT_IDLE || _direction == RIGHT_IDLE ||
			_direction == RIGHT_ATTACK || _direction == RIGHT_RUN)
		{ // 요 네개면 왼쪽 달리기로 바꿔줌
			_direction = LEFT_RUN;			_index = 5;
		}
		else if (_direction == RIGHT_JUMP || _direction == RIGHT_HANG)
		{ // 위 두개면 왼쪽 점프로 바꿔줌 (이하 잡았는지는 점프로 될때 초기화시킴. 잡는게 점프일때니까)
			_direction = LEFT_JUMP;			_index = 4;
			_isGapEum = false;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{ // 왼쪽키를 뗀 상태
		if (_direction == LEFT_RUN)
		{ // 달리고 있었으면 가만히로 바꿔줌
			_direction = LEFT_IDLE;			_index = 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sonicRc.right < WINSIZEX
		&& !KEYMANAGER->isStayKeyDown(VK_LEFT))
	{ // 화면 안에서 오른쪽누른 상태(왼쪽 누른상태면 무시)
		_sonicRc.left += 5;
		_sonicRc.right = _sonicRc.left + SONICWIDTH;
		if (_direction == RIGHT_IDLE || _direction == LEFT_IDLE ||
			_direction == LEFT_ATTACK || _direction == LEFT_RUN)
		{ // 요 네개면 오른쪽 달리기로 바꿔줌
			_direction = RIGHT_RUN;
			_index = 5;
		}
		else if (_direction == LEFT_JUMP || _direction == LEFT_HANG)
		{ // 위 두개면 오른쪽 점프로 바꿔줌 (이하 잡았는지는 점프로 될때 초기화시킴. 잡는게 점프일때니까)
			_direction = RIGHT_JUMP;
			_isGapEum = false;
			_index = 3;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{  // 오른쪽키를 뗀 상태
		if (_direction == RIGHT_RUN)
		{ // 달리고 있었으면 가만히로 바꿔줌
			_direction = RIGHT_IDLE;
			_index = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) && _direction != RIGHT_JUMP && _direction != LEFT_JUMP
		&& !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{ // 점프조건 : 스페이스 누르고 점프중이 아닐때 아래버튼을 누르지 않은 상태(아래누른상태점프는 따로 작동)
		switch (_direction)
		{
		case RIGHT_IDLE:		case RIGHT_RUN:		case RIGHT_ATTACK:		case RIGHT_HANG:
			_direction = RIGHT_JUMP; // 이하 네개는 오른쪽점프로
			_index = 0;
			_isGapEum = false;
			break;
		case LEFT_IDLE:		case LEFT_RUN:		case LEFT_ATTACK:		case LEFT_HANG:
			_direction = LEFT_JUMP; // 이하 네개는 왼쪽점프로
			_index = 7;
			_isGapEum = false;
			break;
		}
		_jumpPower = 8;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{ // 밑점프
		for (int i = 2; i < 5; i++) // 234만 갖고 확인
		{
			if (_sonicRc.bottom + 1 > _object[i].top && _sonicRc.right > _object[i].left &&
				_sonicRc.left < _object[i].right && _sonicRc.top < _object[i].bottom)
			{
				_objectIsNotCollide[i] = true; // 지워버림
				switch (_direction)
				{
				case LEFT_IDLE:				case LEFT_RUN:				case LEFT_ATTACK:
					_jumpPower = 0; // 위 세개면 왼쪽점프로
					_direction = LEFT_JUMP;
					_isGapEum = false;
					_index = 5;
					break;
				case RIGHT_IDLE:				case RIGHT_RUN: 				case RIGHT_ATTACK:
					_jumpPower = 0; // 위 세개면 오른쪽점프로
					_direction = RIGHT_JUMP;
					_isGapEum = false;
					_index = 3;
					break;
				}
				break;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && (_direction == LEFT_IDLE || _direction == RIGHT_IDLE)
		&& _attackReturn >=30) // 공격조건 : 엔터누르고 가만히 있는 상태이며 쿨돌았을때
	{
		switch (_direction)
		{
		case LEFT_IDLE: _direction = LEFT_ATTACK; // 왼쪽 공격으로
			_index = 2;
			_attackReturn = 0;
			break;
		case RIGHT_IDLE: _direction = RIGHT_ATTACK; // 오른쪽 공격으로
			_index = 0;
			_attackReturn = 0;
			break;
		}
	}
}

void playGround::animation()
{ // 애니메이션 잔뜩 모아놓은거
	switch (_direction)
	{
	case LEFT_IDLE:
		if (_index < 0 || _index>10) _index = 10;
		_sonicImg->setFrameY(5);
		_sonicImg->setFrameX(_index);
		if (_index == 10 && _count % 100 != 0) break; // 10에서의 대기시간은 더 길게하려고
		_index--; // 10->9->8->...->0 으로 순환
		break;
	case RIGHT_IDLE:
		if (_index < 0 || _index>10) _index = 0;
		_sonicImg->setFrameY(4);
		_sonicImg->setFrameX(_index);
		if (_index == 0 && _count % 100 != 0) break;
		_index++; // 0->1->2->...->10 으로 순환
		break;

	case LEFT_RUN:
		if (_index < 0 || _index > 5) _index = 5;
		_sonicImg->setFrameY(1);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_RUN:
		if (_index < 0 || _index > 5) _index = 0;
		_sonicImg->setFrameY(0);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	case LEFT_HANG:
		if (_index < 0 || _index > 3) _index = 3;
		_sonicImg->setFrameY(3);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_HANG:
		if (_index < 0 || _index > 3) _index = 0;
		_sonicImg->setFrameY(2);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	case LEFT_ATTACK:
		if (_index < 0 || _index > 2) _index = 2;
		_sonicImg->setFrameY(7);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_ATTACK:
		if (_index < 0 || _index > 2) _index = 0;
		_sonicImg->setFrameY(6);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	case LEFT_JUMP:
		if (_index < 0 || _index > 7) _index = 7;
		if (_index == 2) _index = 4; // 점프 계속 시키려고.. 4->3->2 순환
		_sonicImg->setFrameY(9);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_JUMP:
		if (_index < 0 || _index > 7) _index = 0;
		if (_index == 5) _index = 3; // 점프 계속 시키려고.. 3->4->5 순환
		_sonicImg->setFrameY(8);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	}
}

void playGround::collision()
{ // 인터섹트렉트
	for (int i = 0; i < 6; i++)
	{
		if (IntersectRect(&_temp, &_sonicRc, &_object[i]) && _objectIsNotCollide[i] == false)
		{
			if (_temp.right - _temp.left > _temp.bottom - _temp.top &&
				_object[i].top < _temp.bottom && _object[i].bottom > _temp.bottom && _jumpPower<0) // 착지했다
			{ // 템프의 폭이 높이보다 크고, 템프의 아래가 오브젝트 탑바텀사이에 있으며 점프력이 0보다 작을떄(아래로가고있을때)
				_sonicRc.bottom = _object[i].top; // 밀어주고
				_sonicRc.top = _sonicRc.bottom - SONICHEIGHT;
				switch (_direction) // 아이들로 바꿔줌
				{
				case LEFT_JUMP:					case LEFT_HANG:
					_direction = LEFT_IDLE;
					_index = 10;
					break;
				case RIGHT_JUMP:				case RIGHT_HANG:
					_direction = RIGHT_IDLE;
					_index = 0;
					break;
				}
			}
			else if (_temp.right - _temp.left > _temp.bottom - _temp.top &&
				_object[i].top < _temp.top && _object[i].bottom > _temp.top) // 아래서 박았다
			{
				if (_jumpPower >0) _jumpPower = 0; // 점프파워가 0이상이면 없애버림
			}
			else if (_temp.right - _temp.left <= _temp.bottom - _temp.top &&
				_object[i].left < _temp.right && _object[i].right > _temp.right)
			{ // 왼쪽벽을 잡자
				_sonicRc.right = _object[i].left;
				_sonicRc.left = _sonicRc.right - SONICWIDTH;
				if (_direction == RIGHT_JUMP && _jumpPower <0 &&
					(_sonicRc.top + _sonicRc.bottom) / 2 < _object[i].bottom &&// 소닉의 중점이 오브젝트 바닥보단 위에있어야 잡음
					(_sonicRc.top + _sonicRc.bottom) / 2 > _object[i].top) // 소닉의 중점이 오브젝트 탑보단 아래있어야 잡음					
				{// 벽잡기 (아니면 그냥 부딪힌거)
					if (_temp.bottom - _temp.top < 80) _isGapEum = true;
					// temp의 충돌범위가 낮다면 완전히 잡아서 내려가지 않음
					_direction = RIGHT_HANG;
					_jumpPower = 0;
					_index = 0;
				}
			}
			else if (_temp.right - _temp.left <= _temp.bottom - _temp.top &&
				_object[i].left < _temp.left && _object[i].right > _temp.left)
			{ // 오른쪽벽을 잡자
				_sonicRc.left = _object[i].right;
				_sonicRc.right = _sonicRc.left + SONICWIDTH;
				if (_direction == LEFT_JUMP && _jumpPower < 0 && 
					(_sonicRc.top+_sonicRc.bottom) /2 < _object[i].bottom && // 소닉의 중점이 오브젝트 바닥보단 위에있어야 잡음
					(_sonicRc.top + _sonicRc.bottom) / 2 > _object[i].top) // 소닉의 중점이 오브젝트 탑보단 아래있어야 잡음
				{// 벽잡기 (아니면 그냥 부딪힌거)
					if (_temp.bottom - _temp.top < 80) _isGapEum = true;
					_direction = LEFT_HANG;
					_jumpPower = 0;
					_index = 3;
				}
			}
		}
	}
}

// 바닥이 꺼졌는지 체크합니다.
void playGround::jumpingCheck()
{
	_onGround = false; // 펄스로 초기화
	for (int i = 0; i < 6; i++)
	{
		if (_sonicRc.bottom + 1 > _object[i].top && _sonicRc.right > _object[i].left &&
			_sonicRc.left < _object[i].right && _sonicRc.top < _object[i].bottom)
		{ // 각 오브젝트마다 위에 서있는지 판단(소닉바텀 +1인 가상의 사각형으로 비교함)
			_onGround = true; // 찾으면 true로 바꾸고 브레이크
			break;
		}
	}
	if (!_onGround)
	{ // 이제 떠있는 거임(점프로 바꿔줌)
		switch (_direction)
		{
		case LEFT_RUN: // IDLE이면 밖에 나갈수 없으니깐 생략..
		case LEFT_ATTACK:
			_jumpPower = 0;
			_direction = LEFT_JUMP;
			_isGapEum = false;
			_index = 5;
			break;
		case RIGHT_RUN: // IDLE이면 밖에 나갈수 없으니깐 생략..
		case RIGHT_ATTACK:
			_jumpPower = 0;
			_direction = RIGHT_JUMP;
			_isGapEum = false;
			_index = 3;
			break;
		}
	}
}

// 매달려있는지 체크합니다.
void playGround::hangingCheck()
{
	_isHang = false;
	for (int i = 0; i < 6; i++)
	{
		if (_sonicRc.bottom > _object[i].top && _sonicRc.right > _object[i].left &&
			_sonicRc.left-1 < _object[i].right && _sonicRc.top < _object[i].bottom)
		{ // 각 오브젝트마다 옆에 붙어 있는지 판단(소닉레프트 -1인 가상의 사각형으로 비교함)
			_isHang = true;
			break;
		}
		else if (_sonicRc.bottom > _object[i].top && _sonicRc.right+1 > _object[i].left &&
			_sonicRc.left < _object[i].right && _sonicRc.top < _object[i].bottom)
		{ // 각 오브젝트마다 옆에 붙어 있는지 판단(소닉라이트 +1인 가상의 사각형으로 비교함)
			_isHang = true;
			break;
		}
	}
	if (!_isHang)
	{ // 이제 안붙은거임(점프로 바꿔줌)
		switch (_direction)
		{
		case LEFT_HANG:
			_direction = LEFT_JUMP;
			_isGapEum = false;
			_index = 5;
			break;
		case RIGHT_HANG:
			_direction = RIGHT_JUMP;
			_isGapEum = false;

			_index = 3;
			break;
		}
	}
}

//일정 거리 지나면 오브젝트가 다시 충돌가능
void playGround::objectRegen()
{
	/*if (!IntersectRect(&_temp,&_object[0],&_sonicRc)) _objectIsNotCollide[0] = false;
	if (!IntersectRect(&_temp, &_object[1], &_sonicRc)) _objectIsNotCollide[1] = false;*/
	if (_sonicRc.top > 160) _objectIsNotCollide[2] = false;// 왼쪽 바
	if (_sonicRc.top > 161)	_objectIsNotCollide[3] = false; // 오른쪽 바
	if (_sonicRc.top > 90)	_objectIsNotCollide[4] = false;// 가운데바
}