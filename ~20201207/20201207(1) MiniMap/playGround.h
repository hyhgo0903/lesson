#pragma once
#include "gameNode.h"

enum SIVADIRECTION
{
	SIVA_LEFT_IDLE,
	SIVA_RIGHT_IDLE,
	SIVA_LEFT_RUN,
	SIVA_RIGHT_RUN
};

class playGround : public gameNode
{
private:
	image* _background;
	image* _siva;
	SIVADIRECTION _direction;

	int _count, _index;

	RECT _miniMap;
	RECT _miniP;

	int _cameraX;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용


};

