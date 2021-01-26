#include "stdafx.h"
#include "mainScene.h"

mainScene::mainScene()
{
}

mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	HANDLE file;
	DWORD read;
	file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tile) * TILENUMX*TILENUMY, &read, NULL);
	CloseHandle(file);

	_indexX = _indexY = _count = 0;
	_destX = _destY = _x = _y = 200.f;
	_zerling = RectMakeCenter(_x, _y, 39, 40);
	_destRc = RectMakeCenter(_destX, _destY, 5, 5);

	return S_OK;
}

void mainScene::release()
{
}

void mainScene::update()
{
	if (_count < 5) ++_count;
	else
	{
		_count = 0;
		++_indexY;
		if (_indexY > 6) _indexY = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_destX = _ptMouse.x;
		_destY = _ptMouse.y;
		_angle = getAngle(_x, _y, _destX, _destY);
		if (_angle < 0) _angle += PI2;
		_indexX = (int)((_angle + PI8) / PI4);
		_indexX = 2 -_indexX;
		if (_indexX < 0) _indexX += 8;
		_destRc = RectMakeCenter(_destX, _destY, 5, 5);
	}
	RECT temp;
	if (!IntersectRect(&temp, &_destRc, &_zerling))
	{
		_x += 5 * cosf(_angle);
		_y -= 5 * sinf(_angle);
	}
	_zerling = RectMakeCenter(_x, _y, 39, 40);
}

void mainScene::render()
{
	for (int i = 0; i < TILENUMX * TILENUMY; ++i)
	{ // 각 타일마다 프레임대로 렌더
		IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(),
			_tiles[i]._rc.left, _tiles[i]._rc.top, _tiles[i]._frameX, _tiles[i]._frameY);
	}
	IMAGEMANAGER->findImage("저글링워크")->frameRender(getMemDC(), _zerling.left, _zerling.top, _indexX, _indexY);

	uiRender();
}

