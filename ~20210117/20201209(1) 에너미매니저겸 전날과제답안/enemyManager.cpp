#include "stdafx.h"
#include "enemyManager.h"


/* 1. enemy클래스 안에 적 배열 18개로 만들어져있고 얘가 인클루드 되어있는 경우
한놈씩 상태를 정의해주기 힘들다(특수성)

enemy - enemebullet 구조의 단점(종전)
적죽으면 적의 총알이 지워지는
enemyManager에서 minion // bullet 따로구조가 낫다.
*/


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
		//이터레이터에 별 붙여야..
	}

	_bullet->update();
	minionBulletFire();
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
