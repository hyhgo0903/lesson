#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image*	_imageName;			//왠지 적의 이미지로 쓰일 것 같다
	RECT	_rc;				//왠지 적의 렉트

	int		_currentFrameX;		//적의 프레임 번호 X
	int		_currentFrameY;		//적의 프레임 번호 Y

	int		_count;				//카운트
	int		_fireCount;			//발사 카운트
	int		_rndFireCount;		//랜덤 발사 카운트

	bool _appear; // 끄려면 이게 켜짐

public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	void move();
	void draw();

	bool bulletCountFire();

	//호잇!
	inline RECT getRect() { return _rc; }
	inline bool getAppear() { return _appear; }
	inline void disappear() { _appear = false; }
};

