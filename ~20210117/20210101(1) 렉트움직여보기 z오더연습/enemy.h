#pragma once
#include "gameNode.h"
class enemy : public gameNode
{
protected:
	RECT _rc;
	float _x; float _y;


public:
	enemy();
	~enemy();

	virtual HRESULT init(float x, float y)=0;
	virtual void release();
	virtual void update();
	virtual void render();
	RECT getRect() { return _rc; }


	void rectRender();		//렉트 그리기
};
