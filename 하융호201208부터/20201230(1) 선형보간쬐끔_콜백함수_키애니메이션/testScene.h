#pragma once
#include "gameNode.h"
#include "fun.h"
#include "button.h"

class testScene : public gameNode
{
private:
	fun* _funTest;
	image* _funImage;

	button* _btnSceneChange;

public:
	testScene() {};
	~testScene() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	static void cbSceneChange();
};

