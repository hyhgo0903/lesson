#pragma once
#include "gameNode.h"
#include "effect.h"

class effectTest : public gameNode
{
private:
	effect* _effect;

public:
	effectTest() {};
	~effectTest() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

