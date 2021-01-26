#include "stdafx.h"
#include "enemyBullet.h"

HRESULT enemyBullet::init(int ID, float x, float y, int left = 0, float angle = 0)
{
	_ID = ID;	_x = x;	_y = y;
	switch (_ID)
	{ // 0������(����) 1��Ÿ����(���) 2���ΰ���ġ�ν� 3,4 �ޱ۴�α׳ɽ�
	case 0: _width = 26; _height = 18; _damage = 30;
		_xSpd = 12; _ySpd = 0;	 break;
	case 1: _width = 16; _height = 15; _damage = 30;
		_xSpd = 10.f * cosf(angle); _ySpd = -10.f * sinf(angle);  break;
	case 2: _width = 26; _height = 26; _damage = 20;
		_xSpd = 5.f * cosf(angle); _ySpd = -5.f * sinf(angle);	break;
	case 3: _width = 21; _height = 21; _damage = 20;
		_xSpd = 8.f * cosf(angle); _ySpd = -8.f * sinf(angle);	break;
	case 4: case 5: _width = 24; _height = 24; _damage = 20;
		_xSpd = 7.f * cosf(angle); _ySpd = -7.f * sinf(angle);	break;
	}
	if (_ID < 2 && left > 0) _xSpd *= -1;
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_isFire = true;
	_duration = _frameX = _frameCount = 0;

	return S_OK;
}

void enemyBullet::release()
{

}

void enemyBullet::update()
{
	if (_ID == 1)
	{ // ������ϱ�..
		_ySpd += GRAVITY;
		_xSpd += _wind;
	}
	move();
	_rc = RectMakeCenter(_x, _y, _width, _height);

	if (_ID == 0 && _duration % 3 == 0) ++_frameX;
	if (_ID == 1 && _duration % 3 == 0) ++_frameX;
	if (_ID == 0 && _frameX > 1) _frameX = 0;
	if (_ID == 1 && _frameX > 5) _frameX = 0;
}

void enemyBullet::render()
{
	RECT temp;
	if (IntersectRect(&temp, &CAMERAMANAGER->getMinimapRC(), &_rc)) return; // �̴ϸ��̶� ��ġ�� �ȱ׸�
	if (KEYMANAGER->isToggleKey(VK_TAB))	{	Rectangle(getMemDC(), _rc);	}
	switch (_ID)
	{
	case 0: FINDIMG("���Ѿ�1")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 1: FINDIMG("���Ѿ�2")->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0); break;
	case 2: FINDIMG("���Ѿ�3")->render(getMemDC(), _rc.left, _rc.top); break;
	case 3: FINDIMG("���Ѿ�4")->render(getMemDC(), _rc.left, _rc.top); break;
	case 4: FINDIMG("���Ѿ�5")->render(getMemDC(), _rc.left, _rc.top); break;
	case 5: FINDIMG("���Ѿ�6")->render(getMemDC(), _rc.left, _rc.top); break;
	}

}
