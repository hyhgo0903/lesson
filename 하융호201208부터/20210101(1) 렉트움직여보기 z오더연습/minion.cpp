#include "stdafx.h"
#include "minion.h"

minion::minion()
{
}

minion::~minion()
{
}

HRESULT minion::init(float x, float y)
{
	_rc = RectMakeCenter(x, y, 50, 50);
	return S_OK;
}

void minion::release()
{
}

void minion::update()
{
}

void minion::render()
{
}
