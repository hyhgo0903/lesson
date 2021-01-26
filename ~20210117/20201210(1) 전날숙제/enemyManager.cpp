#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"

//collide함수에 필기해놨음

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
	//collision();
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

			_bullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
				-(PI / 2), 7.0f);
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
	/* 이터레이터가 인덱스보다 느림(but 안정적)
	왜냐면 이터레이터엔 안정적 처리를 위한 기능이 탑재
	(overhead)
	
	벡터랑 달리 리스트같은거 c언어에선 인덱스검사 지원안됨
	(데이터가 많지 않으면 이터레이터검사다보니 느림)

	전날 이터레이터 돌릴떄 erase함수 들어가면
	하나 빠졌는데
	지우고 땡겨지고(?) 없는 주소를 가리키게 됨
	(세그먼트 에러)
	대신 for문이아닌 else절에 ++vi~~해서 처리
	
	*/
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
			break; // 있어야 안 터짐
		}


	}


}
