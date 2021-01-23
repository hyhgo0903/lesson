#include "stdafx.h"
#include "enemyManager.h"


/* 1. enemyŬ���� �ȿ� �� �迭 18���� ��������ְ� �갡 ��Ŭ��� �Ǿ��ִ� ���
�ѳ� ���¸� �������ֱ� �����(Ư����)

enemy - enemebullet ������ ����(����)
�������� ���� �Ѿ��� ��������
enemyManager���� minion // bullet ���α����� ����.
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
		//���ͷ����Ϳ� �� �ٿ���..
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
		//bool ��ȯ���� �� �Լ��� true��~ �̶� ���Դϴ�
		if ((*_viMinion)->bulletCountFire())
		{
			//�Ʊ� enemy�� getRect() inline���� ��������
			RECT rc = (*_viMinion)->getRect();

			_bullet->fire((rc.right + rc.left) / 2, rc.bottom + 5,
				-(PI / 2), 7.0f);
		}
	}

}
