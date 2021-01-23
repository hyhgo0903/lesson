#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:
	image* _mountain;	//마운틴이지만 사실 언덕 이미지
	image* _ball;		//얘는 정말 공

	RECT _rc;			//공에 씌울 렉트
	float _x, _y;		//중점 x, y
	int _probeY;		//Y 탐사축 

public:
	pixelCollision() {};
	~pixelCollision() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

