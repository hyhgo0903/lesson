#pragma once
#include "gameNode.h"
#include "Messenger.h"
#include "enemyManager.h"
#include "MainStage.h"
#include "BossStage.h"
#include "StartScene.h"
#include"DeadScene.h"
class playGround : public gameNode
{
private:
	Messenger* _messenger;
	enemyManager* em;
	POINT camera;//카메라 좌표를 입력받기 위한 변수지정
	float probeDY;//아래 충돌 탐색
	float probeUY;//위 충돌 탐색
	float EprobeDY;//에너미들 중력을 위한
	float probeX;//좌우측 충돌용
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용
	void addImage();
	void pixelCollision();
	void RectCollision();
	POINT getCamera() { return camera; }
};
