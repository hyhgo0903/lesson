#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "player.h"
#include <vector>

class playGround : public gameNode
{
private:
	enemyManager* _em;
	player* _pl;
	vector<int> bottomY;
	char _str[128];
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

};

