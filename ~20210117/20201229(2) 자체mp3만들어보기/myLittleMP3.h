#pragma once
#include "gameNode.h"

enum playMode
{
	CIRCULATE, // 전곡 반복
	ONLYONE, // 한곡만 플레이
	NOCIRCULATE // 반복안함
};


class myLittleMP3 :
	public gameNode
{
private:
	int _nowPlay;
	char _str[128];
	bool _randomOn;
	float _volume; // 0~1
	float _playingTime; // 0~1 비율값임
	playMode _playMode;
	bool _stopped; // 강제로 정지한 경우(현재 상태 알아보거나 다음곡을 틀기 위해 필요)
	bool _silenced;

public:
	myLittleMP3() {};
	~myLittleMP3() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
		
	void clickedList();// 재생목록을 누른 경우
	void clickButtons();// 각종 버튼들을 누른 경우
	void nextMusic(); // 다음으로 넘어감
};

