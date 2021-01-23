#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_alphaValue = rand() % 255;
	_count = _fireCount = 0;

	_rndFireCount = RND->getFromIntTo(1, 800);
	
	_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y, 
		_imageName->getFrameWidth(),
		_imageName->getFrameHeight());

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_count++;

	if (_count % 2 == 0)
	{
		if (_currentFrameX >= _imageName->getMaxFrameX())  _currentFrameX = 0;

		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}

	if (_alphaValue > 0) _alphaValue--;
	else _alphaValue = 255;
}

void enemy::render()
{
	draw();
}

void enemy::move()
{
	
}

void enemy::draw()
{
	_imageName->alphaFrameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY, _alphaValue);
	//_imageName->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _alphaValue);
}

bool enemy::bulletCountFire()
{
	_fireCount++;

	if(_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 800);

		return true;
	}

	return false;
}
