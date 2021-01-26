#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp" // 헤더에 걸어주고
#pragma comment(lib, "lib/fmodex64_vc.lib")
// lib 64비트 비주얼스튜디오 라이브러리를 쓸거야

//API의 PlaySound()로 .wav파일을 재생할 수 있지만
//얘는 버퍼가 X.
//fmod사운드엔진(유니티에도 들어가고 아무튼 그럼)

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5
// 사운드버퍼 10개랑 여분의 채널버퍼 5개
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER
// 합치면 15개

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;

	typedef map<string, Channel**>				arrChannels;
	typedef map<string, Channel**>::iterator	arrChannelIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	arrSounds		_mTotalSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	//   사운드 추가함수(키 값, 음악파일명, 브금or효과음, 루프할껀지)
	void addSound(string keyName, string soundName, bool bgm, bool loop);

	//                             0.0f ~ 1.0f -> 0 ~ 255
	void play(string keyName, float volume = 1.0f);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//호옥시이 몰라서 만들어둠
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
};

