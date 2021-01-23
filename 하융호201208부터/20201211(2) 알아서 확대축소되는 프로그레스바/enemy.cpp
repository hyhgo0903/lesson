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
	_count = _fireCount = 0;

	_rndFireCount = RND->getFromIntTo(1, 800);
	
	_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y, 
		_imageName->getFrameWidth(),
		_imageName->getFrameHeight());
	


	_currentHP = _maxHP = 100;

	_hpBar = new progressBar;
	_hpBar->init(10 + rand()%60, 2+rand()%20);
	// 축소 확대 잘 되는지 보려고 랜덤으루다가 다양하게 넣었읍니다..


	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_count++;

	_hpBar->setPoint((_rc.left + _rc.right) / 2, _rc.top - 10);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();


	if (_count % 2 == 0)
	{
		if (_currentFrameX >= _imageName->getMaxFrameX())  _currentFrameX = 0;

		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}
}

void enemy::render()
{
	draw();
	_hpBar->render();
}

void enemy::move()
{
	
}

void enemy::draw()
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
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