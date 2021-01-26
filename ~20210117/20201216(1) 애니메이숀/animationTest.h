#pragma once
#include "gameNode.h"

class animationTest : public gameNode
{
private:
	image* _camel;

	animation* _ani1;	//디폴트 재생용
	animation* _ani2;	//배열 재생용
	animation* _ani3;	//구간 재생용

public:
	animationTest() {};
	~animationTest() {};

	HRESULT init();
	void release();
	void update();
	void render();

};

