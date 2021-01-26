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
	_hpBar->init(_imageName->getX(), _imageName->getY() - 20, 1580, 420);
	// 이래놔도 spaceship에만 맞춰지고 적용이 안됨
	// 그래서 과제(2)를 한거
	_hpBar->setGauge(_currentHP, _maxHP);

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
	_hpBar->setX(_rc.left);
	_hpBar->setY(_rc.top - 20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
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
