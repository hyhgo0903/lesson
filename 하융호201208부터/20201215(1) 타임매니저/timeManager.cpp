#include "stdafx.h"
#include "timeManager.h"

timeManager::timeManager()
	: _timer(nullptr)
{
}

timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release()
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
	}
}

void timeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;
	SetBkMode(hdc, TRANSPARENT);
	//글자뒤를 투명화할건지 opaque는 불투명
#ifdef _DEBUG // 전처리기 ..  만약에 ~~하면(_DEBUG면)
	{
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
	#else
	{
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif

}
