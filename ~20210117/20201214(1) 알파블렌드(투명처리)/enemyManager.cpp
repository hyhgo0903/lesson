#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("bullet", 30, WINSIZEY);

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	_bullet->update();
	minionBulletFire();
	collision();
}

void enemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();
}

void enemyManager::setMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo;
			ufo = new minion;
			ufo->init("enemy", PointMake(80 + j * 80, 80 + i * 100));
			
			_vMinion.push_back(ufo);
		}
	}
}

void enemyManager::minionBulletFire()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		//bool 반환형인 그 함수가 true면~ 이란 뜻입니당
		if ((*_viMinion)->bulletCountFire())
		{
			//아까 enemy에 getRect() inline으로 만들어뒀죠
			RECT rc = (*_viMinion)->getRect();

			//_bullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
			//	-(PI / 2), 7.0f);

			_bullet->fire((rc.right + rc.left) / 2,
				rc.bottom + 5,
				getAngle((rc.right + rc.left) / 2, rc.bottom + 5,
					_ship->getShipImage()->getCenterX(),
					_ship->getShipImage()->getY()), 7.0f);

		}
	}

}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp,
			&_bullet->getVBullet()[i].rc,
			&RectMake(_ship->getShipImage()->getX(),
				_ship->getShipImage()->getY(),
				_ship->getShipImage()->getWidth(),
				_ship->getShipImage()->getHeight())))
		{
			_bullet->removeBullet(i);
			_ship->hitDamage(10);
			break;
		}


	}


}
