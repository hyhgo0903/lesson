#pragma once
#include "gameNode.h"

enum STATE
{
	PHASE_1,
	PHASE_2,
	PHASE_3,
	PHASE_BOSS
};

class enemy : public gameNode
{
protected:
	image*	_imageName;			//왠지 적의 이미지로 쓰일 것 같다
	RECT	_rc;				//왠지 적의 렉트

	int		_currentFrameX;		//적의 프레임 번호 X
	int		_currentFrameY;		//적의 프레임 번호 Y

	int _toX, _toY; // 목적지
	int _tempX, _tempY; // 페이즈3에서 잠깐잠깐 목적지
	int _x, _y; // 현재위치
	bool _arrived; // 첫리젠해서 도착했는지
	int _direction; // 방향 1이나 -1로
	float _angle;


	int		_count;				//카운트
	int		_fireCount;			//발사 카운트
	int		_rndFireCount;		//랜덤 발사 카운트
	int     _countAgain;		//또 카운트..(페이즈3에서 자리 향하는거)

	int _bossPhase; // 더러워지는게 느껴진다

	STATE _state;
public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position, STATE state);
	void release();
	void update();
	void render();

	void move();
	void draw();

	bool bulletCountFire();

	//호잇!
	inline RECT getRect() { return _rc; }
	inline STATE getState() { return _state; }
	inline int getBossState() { return _bossPhase; }
	void phaseShift();
};

