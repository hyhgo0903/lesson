#include "stdafx.h"
#include "Bullet.h"

HRESULT Bullet::init(const char* imageName,int bulletMax, float range)
{
	_imgName = imageName;
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void Bullet::release()
{
}

void Bullet::update()
{
	move();
}

void Bullet::render(POINT camera)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,camera,0,_viBullet->direction);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
		{
			Rectangle(getMemDC(), _viBullet->rc, camera);
		}
	}
}

void Bullet::fire(float x, float y, float speed,int direction)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imgName);
	bullet.speed = speed;
	bullet.width = bullet.bulletImage->getWidth();
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.direction = direction;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	_vBullet.push_back(bullet);
}

void Bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if(_viBullet->direction==0)_viBullet->x -=  _viBullet->speed;
		if (_viBullet->direction == 1)_viBullet->x += _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Bullet::removeMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

