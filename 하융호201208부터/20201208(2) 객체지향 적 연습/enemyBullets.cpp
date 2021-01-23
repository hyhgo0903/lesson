#include "stdafx.h"
#include "enemyBullets.h"

HRESULT enemyBullets::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; ++i)
	{
		tagEnemyBullet enemyBullet;
		ZeroMemory(&enemyBullet, sizeof(enemyBullet));
		enemyBullet.enemyBulletImage = new image;
		enemyBullet.enemyBulletImage->init("bullet.bmp", 21, 21, true, RGB(255, 0, 255));
		enemyBullet.speed = -15.0f;
		enemyBullet.isFire = false;

		_vEnemyBullet.push_back(enemyBullet);
	}

	return S_OK;
}

void enemyBullets::release()
{
	_vEnemyBullet.clear();
}

void enemyBullets::update()
{
	move();
}

void enemyBullets::render()
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		if (!_viEnemyBullet->isFire) continue;

		_viEnemyBullet->enemyBulletImage->render(getMemDC(),
			_viEnemyBullet->rc.left,
			_viEnemyBullet->rc.top,
			0, 0,
			_viEnemyBullet->enemyBulletImage->getWidth(),
			_viEnemyBullet->enemyBulletImage->getHeight());
	}
}

void enemyBullets::fire(float x, float y)
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		if (_viEnemyBullet->isFire) continue;

		_viEnemyBullet->isFire = true;
		_viEnemyBullet->x = _viEnemyBullet->fireX = x;
		_viEnemyBullet->y = _viEnemyBullet->fireY = y;
		_viEnemyBullet->rc = RectMakeCenter(_viEnemyBullet->x, _viEnemyBullet->y,
			_viEnemyBullet->enemyBulletImage->getWidth(),
			_viEnemyBullet->enemyBulletImage->getHeight());

		break;
	}

}

void enemyBullets::move()
{
	for (_viEnemyBullet = _vEnemyBullet.begin(); _viEnemyBullet != _vEnemyBullet.end(); ++_viEnemyBullet)
	{
		if (!_viEnemyBullet->isFire) continue;

		_viEnemyBullet->y -= _viEnemyBullet->speed;
		_viEnemyBullet->rc = RectMakeCenter(_viEnemyBullet->x, _viEnemyBullet->y,
			_viEnemyBullet->enemyBulletImage->getWidth(),
			_viEnemyBullet->enemyBulletImage->getHeight());

		if (_range < getDistance(_viEnemyBullet->fireX, _viEnemyBullet->fireY, _viEnemyBullet->x, _viEnemyBullet->y))
		{
			_viEnemyBullet->isFire = false;
		}
	}

}