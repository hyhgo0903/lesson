#pragma once
#include "gameNode.h"
#include "tile.h"
#include "mapTool.h"

class mainScene :public gameNode
{
private:
	tile _tiles[TILENUMX*TILENUMY];
	RECT _zerling;
	float _destX, _destY, _x, _y, _angle;
	RECT _destRc;
	int _indexX, _indexY, _count;

public:
	mainScene();
	~mainScene();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void uiRender();
};

