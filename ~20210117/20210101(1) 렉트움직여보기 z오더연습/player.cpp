#include "stdafx.h"
#include "player.h"
#include "STATE.h"
#include "Idle.h"
#include "Jump.h"
#include "walk.h"
#include "run.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	_imgX = _groundX = 100.f;
	_imgY = _groundY = 300.f;
	_directionChanged = _directionChangeCount = _dirMemory = _dirMemoryCount = 0;
	_imgRc = RectMakeCenter(_imgX, _imgY, 50, 50);
	_groundRc = RectMakeCenter(_groundX, _groundY, 20, 20);
	_altitude = 0.f;
	_left = false;
	setState(IDLE);
	//setState(IDLE);
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_statePattern->updateState();
	_imgRc = RectMakeCenter(_imgX, _imgY, 50, 50);
	_groundRc = RectMakeCenter(_groundX, _groundY, 50, 50);	
	minusDirectionChanged();
}

void player::render()
{
	switch (_enumState)
	{
	case IDLE: sprintf_s(_str, "IDLE");		break;
	case JUMP: sprintf_s(_str, "JUMP");		break;
	case WALK: sprintf_s(_str, "WALK");		break;
	case RUN: sprintf_s(_str, "RUN");		break;
	}
	TextOut(getMemDC(), 0, 60, _str, strlen(_str));
	if (_left > 0) sprintf_s(_str, "LEFT");
	else if (_left == 0) sprintf_s(_str, "RIGHT");
	TextOut(getMemDC(), 60, 60, _str, strlen(_str));
	if (_directionChanged >= 2)
	{ // 방향이 0.5초내 두번 바뀌었다 == 좌우(or우좌)입력을 한 상태임
		sprintf_s(_str, "이때 버튼을 누르면 특수기로 나가도록 설정");
		TextOut(getMemDC(), 0, 80, _str, strlen(_str));
	}
}

void player::minusDirectionChanged()
{
	if (_directionChanged > 0) // 방향전환이 일어났다면
	{
		if (_directionChanged > 2) _directionChanged = 2; // 방향전환 2번 넘으면 2번으로 해주고
		++_directionChangeCount; // 카운트센다
		if (_directionChangeCount > 30) // 30(0.5초) 이상 지났다면
		{
			_directionChangeCount = 0; // 카운트 0으로 돌리고
			--_directionChanged; // 방향전환 줄여줌
		}
	} // 참고 : 방향전환 두 번 일어난 경우 특수키 사용조건으로 함

	if (_dirMemory > 0) // 뭔가 기억되어 있다면
	{
		++_dirMemoryCount;
		if (_dirMemoryCount > 30)
		{ // 30(0.5초)카운트내로 초기화 시켜줌
			_dirMemoryCount = 0;
			_dirMemory = 0;
		}
	}
}

void player::rectRender()
{
	Rectangle(getMemDC(), _groundRc);
	Rectangle(getMemDC(), _imgRc);
}

//상태설정

void player::setState(State state)
{
	if (_statePattern)_statePattern->ExitState();
	_enumState = state;
	switch (state)
	{
	case IDLE:	_statePattern = new Idle;	break;
	case JUMP:	_statePattern = new Jump;	break;
	case WALK:	_statePattern = new walk;	break;
	case RUN:	_statePattern = new run;	break;
	}
	_statePattern->LinkMemberAdress(this);
	_statePattern->EnterState();
}
