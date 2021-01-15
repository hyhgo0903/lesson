#pragma once
#include "singletonBase.h"
#include <bitset> // 0,1 눌러졌냐 아니냐

// 무슨무슨 매니저 : 싱글톤임
#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase <keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//키를 한 번만 눌렀다면
	bool isOnceKeyDown(int key);

	//키를 눌렀다가 떼면
	bool isOnceKeyUp(int key);

	//키를 계속 누르고 있으면
	bool isStayKeyDown(int key);

	//키가 토글되면
	//한번 누르면 ON, 다시 누르면 OFF
	bool isToggleKey(int key);

	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
};

