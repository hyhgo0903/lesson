#include "stdafx.h"
#include "playGround.h"

siva::siva()
{
}


siva::~siva()
{
}

//초기화는 여기다 하세요
HRESULT siva::init()
{
	_background = IMAGEMANAGER->addImage("깜장이", "background.bmp", 1440, 2096, false, RGB(255, 0, 255));
	// 번거롭겠지만 맵사이즈 stdafx.h에서 맞게 지정해주세요

	_siva = IMAGEMANAGER->addFrameImage("시바", "siva_run.bmp", 832, 208, 8, 2, true, RGB(255, 0, 255));
	_siva->setFrameY(0);
	_sivaRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	_enemy = RectMake(WINSIZEX - 110, WINSIZEY - 110, 100, 100);
	_count = _index = _vibrateCount = 0;

	_direction = SIVA_RIGHT_IDLE;

	return S_OK;
}

//메모리 해제는 여기다 하세요
void siva::release()
{
}

//연산(계산)은 여기다 하세요
void siva::update()
{
	sivaaa(); // 양썜이 작성하신 시바. 보려면 밑에 참조

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		CAMERAMANAGER->vibrate();
	}
	// 스페이스 누른상태면 흔들림

	// 진동함수 활용 예 (이해안가면 스킵)
	if (IntersectRect(&_temp, &_sivaRc, &_enemy))
	{
		_enemy = { 0,0,0,0 }; // 부딪히면 대충 치우도록 했음
		_vibrateOn = true; // 진동 on
		_vibrateCount = 0; // 진동 카운트 초기화
	}
	if (_vibrateOn) // 진동 on이면
	{
		_vibrateCount++; // 진동카운트는 올라감
		CAMERAMANAGER->vibrate(); // 진동함수
		if (_vibrateCount > 50) _vibrateOn = false; // 일정량 이상이면 꺼준다
	}
	// 요약 : 일정기간 지속하려면 불이랑 카운트를 만들고 인터섹트렉트되면 불값을 켜주고
	// 카운트 초기화됨 -> 카운트 계속 올라가서 일정 이상되면 다시 불이 꺼짐


	//CAMERAMANAGER->focusOnRect(_sivaRc); // 걍 이렇게 쓰면 중앙으로 맞춰줌(기본값 2,2)
	CAMERAMANAGER->focusOnRect(_sivaRc, 3, 4); // 화면의 x축으로 1/3지점 y축으로 1/4지점에서 스크롤됩니다


	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (CAMERAMANAGER->getCameraLock()) CAMERAMANAGER->cameraLockOff();
		else CAMERAMANAGER->cameraLock();
	}
}

//제발 여기다 그려라 좀...
void siva::render()
{
	_background->render(getMemDC(), 0, 0);
	_siva->frameRender(getMemDC(), _sivaRc.left, _sivaRc.top);
	Rectangle(getMemDC(), _enemy);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _sivaRc);
	} // 배경과 적과 시바를 그립니다


	CAMERAMANAGER->minimap(getMemDC(), 20, 20, 150, 150); // 미니맵 틀 그리기(미니맵이 윈도우창 기준)
	//CAMERAMANAGER->minimap(backDC, 20, 20, 150, 150, true); // 위 대신 이걸하면 미니맵이 전체맵기준임
	CAMERAMANAGER->minimapObject(getMemDC(), _sivaRc); // 미니맵 틀 그리는게 없다면 작동하지 않음
	CAMERAMANAGER->minimapObject(getMemDC(), _enemy); // 미니맵 틀 그리는게 없다면 작동하지 않음

	/* 미니맵에 적 추가하고 싶으면 다음과 같이 그려줍시다
	for (int i = 0; i < ENEMYMAX; i++)
	{
		CAMERAMANAGER->miniMapObject(backDC, _enemy[i]);
	}
	*/
}


// 양썜이 작성하신 시바
void siva::sivaaa()
{

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _sivaRc.top > 0)
	{
		_sivaRc.top -= 3;
		_sivaRc.bottom = _sivaRc.top + 100;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _sivaRc.bottom < MAPSIZEY)
	{
		_sivaRc.top += 3;
		_sivaRc.bottom = _sivaRc.top + 100;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sivaRc.left > 0)
	{
		_sivaRc.left -= 3;
		_sivaRc.right = _sivaRc.left + 100;
		_direction = SIVA_LEFT_RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_direction = SIVA_LEFT_IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sivaRc.right < MAPSIZEX)
	{
		_sivaRc.left += 3;
		_sivaRc.right = _sivaRc.left + 100;
		_direction = SIVA_RIGHT_RUN;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_direction = SIVA_RIGHT_IDLE;
	}

	_count++;
	if (_count % 10 == 0)
	{
		switch (_direction)
		{
		case SIVA_LEFT_IDLE:
			if (_index <= 5) _index = 7;
			_siva->setFrameY(1);
			_siva->setFrameX(_index);
			_index--;
			break;
		case SIVA_RIGHT_IDLE:
			if (_index >= 2) _index = 0;
			_siva->setFrameY(0);
			_siva->setFrameX(_index);
			_index++;
			break;
		case SIVA_LEFT_RUN:
			if (_index <= -1) _index = 5;
			_siva->setFrameY(1);
			_siva->setFrameX(_index);
			_index--;
			break;
		case SIVA_RIGHT_RUN:
			if (_index >= _siva->getMaxFrameX()) _index = 2;
			_siva->setFrameY(0);
			_siva->setFrameX(_index);
			_index++;
			break;
		}
		_count = 0;
	}
}

