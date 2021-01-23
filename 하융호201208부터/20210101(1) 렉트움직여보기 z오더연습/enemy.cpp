#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(float x, float y)
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	
}

void enemy::render()
{
}

void enemy::rectRender()
{
	Rectangle(getMemDC(), _rc);
}
