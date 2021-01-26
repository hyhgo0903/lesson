#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{

	for (int i = 0; i < 18; ++i)
	{
		tagEnemy enemy;
		ZeroMemory(&enemy, sizeof(enemy));
		enemy.enemyImage = new image;
		enemy.enemyImage->init("enemy.bmp", 88, 78, 2, 1, true, RGB(255, 0, 255));
		enemy.index = 0;
		enemy.enemyImage->setFrameY(0);
		enemy.appear = true;
		enemy.rc = RectMake(30+(i % 6) * 100, 10 + (i / 6) * 100, 44, 78);
		enemy.count = rand()%50;

		_vEnemy.push_back(enemy);
	}
	
	_enemyBullets = new enemyBullets;
	_enemyBullets->init(300, WINSIZEY);

	return S_OK;
}

void enemy::release()
{
	_vEnemy.clear();
}

void enemy::update()
{
	_enemyBullets->update();
}

void enemy::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		if (_viEnemy->appear == false) continue;
		_viEnemy->enemyImage->frameRender(getMemDC(),
			_viEnemy->rc.left,
			_viEnemy->rc.top,
			_viEnemy->index, 0);

		_viEnemy->count++;

		if (_viEnemy->count % 50 == 0)
		{
			// 요거는 작동함
			_viEnemy->index++;
			if (_viEnemy->index >= 2) _viEnemy->index = 0;

			/* 이거 작동 안됨(한번 움직이고 멈춤)
			_viEnemy->enemyImage->setFrameX(_viEnemy->enemyImage->getFrameX()+1);
			if (_viEnemy->enemyImage->getFrameX() > 1)
			{
				_viEnemy->enemyImage->setFrameX(0);
			}

			// 요거는 작동함
			_viEnemy->enemyImage->setFrameX(_viEnemy->enemyImage->getFrameX() - 1);
			if (_viEnemy->enemyImage->getFrameX() < 0)
			{
				_viEnemy->enemyImage->setFrameX();
			}*/

			if (rand() % 4 == 0) 
			{
				_enemyBullets->fire((_viEnemy->rc.left + _viEnemy->rc.right) / 2,
					_viEnemy->rc.bottom); // 쏘는건 이거고
			}
			_viEnemy->count = 0;
		}
	}
	_enemyBullets->render();
}
