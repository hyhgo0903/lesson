#pragma once
#include "gameNode.h"
class STATE;
enum State {
	IDLE,
	JUMP,
	WALK,
	RUN
};

class player :
	public gameNode
{
private:
	float _imgX; float _imgY;		// 점프하면 위에
	RECT _imgRc;
	float _groundX; float _groundY; // 땅에 붙는RC
	RECT _groundRc;
	bool _left;					// 왼쪽을 보고 있는지
	State _enumState;
	STATE* _statePattern;
	float _altitude;			// 점프시 높이
	char _str[128];
	int _directionChanged;		// 좌우가 몇번 바뀌었는지 카운트(커맨드)
	int _directionChangeCount;	// 카운트체크해서 내림
	int _dirMemory;				// 방향 기억(대쉬용)
	int _dirMemoryCount;		// 카운트체크해서 내림

public:
	player();
	~player();
	HRESULT init();
	void release();
	void update();
	void render();

	void minusDirectionChanged();

	void rectRender();		//렉트 그리기

	void setState(State state);
	RECT getGroundRc() { return _groundRc; }
	RECT getImgRc() { return _imgRc; }
	float& getGroundX() { return _groundX; }float& getGroundY() { return _groundY; }
	float& getImgX() { return _imgX; }		float& getImgY() { return _imgY; }
	bool& getLeft() { return _left; }
	State& getEnumState() { return _enumState; }
	void plusDirectionChanged() { ++_directionChanged; }
	int& getDirMemory() {return _dirMemory;}
};

