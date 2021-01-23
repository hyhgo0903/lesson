#pragma once
#include "enemy.h"
class minion :	public enemy
{

public:
	minion();
	~minion();

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

