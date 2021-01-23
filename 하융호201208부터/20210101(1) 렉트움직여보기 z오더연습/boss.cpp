#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init(float x, float y)
{
	_rc=RectMakeCenter(x, y, 100, 100);
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
}

void boss::render()
{
}
