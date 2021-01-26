#include "stdafx.h"
#include "myLittleMP3.h"

HRESULT myLittleMP3::init()
{
	_randomOn = _silenced = false;
	_nowPlay = 0;
	_stopped = true;
	sprintf_s(_str, "%d", _nowPlay);
	_volume = 1.0f;
	_playingTime = 0.f;
	_playMode = CIRCULATE;
	srand(time(NULL));
	SOUNDMANAGER->addSound("0", "music/Alan Walker & Au Ra & Tomine Harket - Darkside.mp3", true, false);
	SOUNDMANAGER->addSound("1", "music/Alan Walker & Sabrina Carpenter & Farruko - On My Way.mp3", true, false);
	SOUNDMANAGER->addSound("2", "music/IU - Love poem.mp3", true, false);
	SOUNDMANAGER->addSound("3", "music/Jvcki Wai, 영비(Young B), Osshun Gum, 한요한 - 띵 (Prod. By 기리보이).mp3", true, false);
	SOUNDMANAGER->addSound("4", "music/NOMA - Brain Power.mp3", true, false);
	SOUNDMANAGER->addSound("5", "music/The Chainsmokers & Coldplay - Something Just Like This.mp3", true, false);
	SOUNDMANAGER->addSound("6", "music/Zedd & Alessia Cara - Stay.mp3", true, false);
	SOUNDMANAGER->addSound("7", "music/에픽하이 - BLEED.mp3", true, false);
	SOUNDMANAGER->addSound("8", "music/에픽하이 - 술이 달다 (Feat. 크러쉬).mp3", true, false);
	SOUNDMANAGER->addSound("9", "music/태연 - 사계 (Four Seasons).mp3", true, false);
	return S_OK;
}

void myLittleMP3::release()
{
}

void myLittleMP3::update()
{	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && GetFocus())
	{
		clickedList();
		clickButtons();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && GetFocus())
	{
		// 볼륨
		if (_ptMouse.x > 276 && _ptMouse.y > 120 && _ptMouse.x < 329 && _ptMouse.y < 130)
		{
			_volume = ((float)_ptMouse.x - 276.f) / 53.f;
			_silenced = false;
			SOUNDMANAGER->setVolume(_volume);
		}

		// 재생바
		if (_ptMouse.x >= 11 && _ptMouse.y >= 140 && _ptMouse.x <= 330 && _ptMouse.y <= 148)
		{
			_playingTime = ((float)_ptMouse.x - 11.f) / 319.f;
			SOUNDMANAGER->setPoint(_str, _playingTime);
		}
	}
	_playingTime = SOUNDMANAGER->getPortion(_str);
	if (!SOUNDMANAGER->isPlaySound(_str) && !_stopped)
	{
		nextMusic();
	}
}

void myLittleMP3::render()
{
	FINDIMG("배경")->render(getMemDC());
	FINDIMG("선택")->render(getMemDC(), 6, 221 + _nowPlay*24);
	if (!SOUNDMANAGER->isPlaySound(_str) || SOUNDMANAGER->isPauseSound(_str))
	{
		FINDIMG("플레이버튼")->render(getMemDC(),0,157);		
	}
	FINDIMG("pic")->frameRender(getMemDC(), 120, 8, _nowPlay, 0);
	FINDIMG("볼륨")->render(getMemDC(), 276, 120, 0, 0, 53.f*_volume, 10);
	FINDIMG("재생바")->render(getMemDC(), 11, 143, 0, 0, 319.f*_playingTime, 2);
	if (_randomOn) FINDIMG("랜덤")->render(getMemDC(), 271, 161);
	if (_silenced) FINDIMG("음소거")->render(getMemDC(), 256, 119);
	if (_playMode == NOCIRCULATE) FINDIMG("반복안함")->render(getMemDC(), 308, 159);
	else if (_playMode == ONLYONE) FINDIMG("한곡")->render(getMemDC(), 308, 159);
	
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	char temp[256];
	int tempTime = SOUNDMANAGER->getTime(_str) / 1000 % 60;
	sprintf_s(temp, "%02d", tempTime); // 초
	TextOut(getMemDC(), 41, 116, temp, strlen(temp));
	tempTime = SOUNDMANAGER->getTime(_str) / 60000; //분
	sprintf_s(temp, "%d :", tempTime);
	TextOut(getMemDC(), 21, 116, temp, strlen(temp));
}

void myLittleMP3::clickedList()
{ // 재생목록 글자 누른경우
	for (int i = 0; i < 10; ++i)
	{
		if (_ptMouse.y > 221 + 24 * i && _ptMouse.y < 245 + 24 * i && _ptMouse.x > 28 && _ptMouse.x < 280)
		{
			SOUNDMANAGER->stop(_str);
			_nowPlay = i;
			sprintf_s(_str, "%d", _nowPlay);
			if (_silenced) SOUNDMANAGER->play(_str, 0.f);
			else SOUNDMANAGER->play(_str, _volume);
			_stopped = false;
			break;
		}
	}
}

void myLittleMP3::clickButtons()
{
	// 플레이버튼
	if (_ptMouse.x > 9 && _ptMouse.y > 160 && _ptMouse.x < 28 && _ptMouse.y < 182)
	{
		if (SOUNDMANAGER->isPauseSound(_str))
		{
			SOUNDMANAGER->resume(_str);
		}
		else if (SOUNDMANAGER->isPlaySound(_str))
		{
			SOUNDMANAGER->pause(_str);
		}
		else
		{
			if (_silenced) SOUNDMANAGER->play(_str, 0.f);
			else SOUNDMANAGER->play(_str, _volume);
			_stopped = false;
		}
	}

	// 중지
	if (_ptMouse.x > 33 && _ptMouse.y > 162 && _ptMouse.x < 50 && _ptMouse.y < 182)
	{
		_stopped = true;
		SOUNDMANAGER->stop(_str);
	}

	// 랜덤
	if (_ptMouse.x > 274 && _ptMouse.y > 162 &&	_ptMouse.x < 300 && _ptMouse.y < 182)
	{
		if (_randomOn) _randomOn = false;
		else _randomOn = true;
	}

	// 재생모드
	if (_ptMouse.x > 309 && _ptMouse.y > 160 &&	_ptMouse.x < 330 && _ptMouse.y < 182)
	{
		switch (_playMode)
		{
		case CIRCULATE: _playMode = ONLYONE;			break;
		case ONLYONE: _playMode = NOCIRCULATE;			break;
		case NOCIRCULATE: _playMode = CIRCULATE;		break;
		}
	}

	// 이전곡
	if (_ptMouse.x > 53 && _ptMouse.y > 160 && _ptMouse.x < 73 && _ptMouse.y < 182)
	{
		if (SOUNDMANAGER->getTime(_str) > 5000)
		{
			SOUNDMANAGER->setPoint(_str, 0);
			return;
		}	// 일정시간(5초) 이상이면 처음으로 보냄
		SOUNDMANAGER->stop(_str);
		if (_randomOn)
		{
			_nowPlay += rand() % 9 + 1;
			_nowPlay %= 10;		// 1~9을 더하고 나머지10을 합니다.(지가 다시 안걸리게 하기 위해서)
			sprintf_s(_str, "%d", _nowPlay);
			if (!_stopped)
			{
				if (_silenced) SOUNDMANAGER->play(_str, 0.f);
				else SOUNDMANAGER->play(_str, _volume);
			}

		}
		else
		{
			--_nowPlay;
			if (_nowPlay < 0) _nowPlay = 9;
			sprintf_s(_str, "%d", _nowPlay);
			if (!_stopped)
			{
				if (_silenced) SOUNDMANAGER->play(_str, 0.f);
				else SOUNDMANAGER->play(_str, _volume);
			}
		}
	}

	// 다음곡
	if (_ptMouse.x > 76 && _ptMouse.y > 160 && _ptMouse.x < 94 && _ptMouse.y < 182)
	{
		if (_nowPlay < 9 && _playMode==ONLYONE) ++_nowPlay;
		if (_nowPlay == 9 && _playMode == ONLYONE) _nowPlay = 0;
		nextMusic();		
	}

	// 음소거
	if (_ptMouse.x > 254 && _ptMouse.y > 117 && _ptMouse.x < 275 && _ptMouse.y < 134)
	{
		if (_silenced)
		{
			_silenced = false;
			SOUNDMANAGER->setVolume(_volume);
		}
		else
		{
			_silenced = true;
			SOUNDMANAGER->setVolume(0);
		}
	}

}

void myLittleMP3::nextMusic()
{
	SOUNDMANAGER->stop(_str);
	if (_playMode == ONLYONE)
	{
		if (_silenced) SOUNDMANAGER->play(_str, 0.f);
		else SOUNDMANAGER->play(_str, _volume); 
	}
	else if (_randomOn)
	{
		_nowPlay += rand() % 9 + 1;
		_nowPlay %= 10;		// 1~9을 더하고 나머지10을 합니다.(지가 다시 안걸리게 하기 위해서)
		sprintf_s(_str, "%d", _nowPlay);
		if (!_stopped)
		{
			if (_silenced) SOUNDMANAGER->play(_str, 0.f);
			else SOUNDMANAGER->play(_str, _volume);
		}
	}
	else
	{
		++_nowPlay;
		if (_nowPlay > 9) _nowPlay = 0;
		sprintf_s(_str, "%d", _nowPlay);
		if (_playMode != CIRCULATE && _nowPlay == 0)
		{
			_stopped = true;
		} // 노서큘레이트면 막곡끝날떄 꺼줌
		else
		{
			if (_silenced) SOUNDMANAGER->play(_str, 0.f);
			else SOUNDMANAGER->play(_str, _volume);
		}
	}
}
