#include "stdafx.h"
#include "effectTest.h"

HRESULT effectTest::init()
{
	IMAGEMANAGER->addImage("����", "explosion.bmp", 832, 62, true, RGB(255, 0, 255));

	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("����"), 32, 62, 1, 0.5f);

	EFFECTMANAGER->addEffect("explosion", "explosion.bmp", 832, 62, 32, 62, 1.0f, 0.3f, 1000);

	return S_OK;
}

void effectTest::release()
{
}

void effectTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("explosion", _ptMouse.x, _ptMouse.y);
	}
	EFFECTMANAGER->update();
	_effect->update();
	
}

void effectTest::render()
{
	EFFECTMANAGER->render();
	_effect->render();
	
}
