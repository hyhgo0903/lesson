#include "stdafx.h"
#include "bullets.h"

/*
정적할당은 삭제가 안된다(메모리해제할 길이 없다)
단점 : 미리만들어둬야함(30발 정해놓고 걔만쓸게)
그렇다고 너무 많이 만들면 메모리 낭비가 심함
안쓸떄 지워주고 싶은데..

동적할당>>
calloc / malloc (c) -> new alloc방식(c++)
메모리 만들고 지우고 -> 메모리 파편화 -> 할당공간 찾기 곤란(느리다)

가비지컬렉터 -> 메모리 참조하고 있다가 안쓰는거를 그제서야 날림(제어권한은 x)
-> 유니티는 오브젝트풀을 쓴다

오브젝트풀 : new(x) delete(x) 풀에서 꺼내 쓴다(new안하고) -> 쓰면 넣어놓는다(delete 안하고)
풀의 규모를 축소할수O


*/


HRESULT missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; ++i) // ++i한건 빨라서
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		//패딩바이트 몬지 알아둘것
		//ZeroMemory ->Memset 메모리를 0으로
		bullet.bulletImage = new image;
		bullet.bulletImage->init("missile1.bmp", 26, 124, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release()
{
	_vBullet.clear();
}

void missile::update()
{
	move();
}

void missile::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->bulletImage->render(getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top,
			0, 0,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
	}
}

void missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		break;
	}

}

void missile::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet->isFire = false;
		}
	}
}

HRESULT rectMissile::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;


	return S_OK;
}

void rectMissile::release()
{
}

void rectMissile::update()
{
	move();
}

void rectMissile::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void rectMissile::fire(float x, float y)
{
	//-명-
	//입력한 최대값보다 벡터사이즈가 큰데 더 생성하면 안되니까 종료시킴(return;)
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 0, 0, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 6.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	_vBullet.push_back(bullet);
}

void rectMissile::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{ // for에다 ++_viBullet하면 안됨 (vector에서 erase했을 때 뻑남)
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y,
			_viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->bulletImage);
			SAFE_DELETE(_viBullet->bulletImage);
			// 이거 안하면 계속 축적
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}

}
