#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"

//collide�Լ��� �ʱ��س���

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("bullet", 600, WINSIZEY);

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
			ufo->init("enemy", PointMake(100 + j * 80, 80 + i * 100), PHASE_1);

			_vMinion.push_back(ufo);
		}
	}
}

void enemyManager::regenMinion(int num)
{
	switch (num)
	{
	case 0: // �ι�° �� ����
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				enemy* ufo;
				ufo = new minion;
				ufo->init("enemy", PointMake(100 + j * 80, 80 + i * 100), PHASE_2);

				_vMinion.push_back(ufo);
			}
		}
		break;
	case 1: // ����° �� ����
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				enemy* ufo;
				ufo = new minion;
				ufo->init("enemy", PointMake(100 + j * 80, 80 + i * 100), PHASE_3);

				_vMinion.push_back(ufo);
			}
		}
		break;
	case 2: // ���� ����
		enemy* ufo;
		ufo = new minion;
		ufo->init("boss", PointMake(WINSIZEX/2,200), PHASE_BOSS);

		_vMinion.push_back(ufo);
		break;
	}
}

void enemyManager::minionBulletFire()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		//bool ��ȯ���� �� �Լ��� true��~ �̶� ���Դϴ�
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			switch ((*_viMinion)->getBossState())
			{
			case 0: // ������ ��Ÿ���� ��
			//�Ʊ� enemy�� getRect() inline���� ��������
				_bullet->fire((rc.right + rc.left) / 2, rc.bottom + 5 ,
					-(PI / 2), 7.0f);
				break;			
			case 1: // �����ϰ� �� ��°�(������ ǳ��) �䳻
				_bullet->fire((rc.right + rc.left) / 2.0, rc.top + 43.0,
					(float)(rand()%629) /100.0, 14.0f);

				// ����ź ��Ÿ� ��ø��� �̷���
				//for (int i = 0; i < 63; i++)
				//{
				//	_bullet->fire((rc.right + rc.left) / 2.0, rc.top + 43.0, //��ġ�� ������
				//		(float)i / 10.0, 14.0f);
				//}
				
				break;
			case 2: // ������������ ǥ���Ϸ� ������ ����� �ø�..
				for (float i = 0.0; i < 8; i++)
				{
					_bullet->fire(rc.left+ 40+20*i, rc.bottom,
						- PI/2, 14.0f);
				}
				break;
			case 3: // ����ġ�� 10�߾� �߻�(�ֵ���Ŀ�� ��� ������)
				for (float i = 0.0; i < 10.0; i++)
				{
					int x = rc.left + rand() % 223;
					int y = rc.top + rand() % 175;
					_bullet->fire(x, y,
						getAngle(x, y, _ship->getShipImage()->getX(),
							_ship->getShipImage()->getY()), 14.0f);
				}// ��ȣ������ �迡 Ȱ��
				break;

			}
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
	/* ���ͷ����Ͱ� �ε������� ����(but ������)
	�ֳĸ� ���ͷ����Ϳ� ������ ó���� ���� ����� ž��
	(overhead)
	
	���Ͷ� �޸� ����Ʈ������ c���� �ε����˻� �����ȵ�
	(�����Ͱ� ���� ������ ���ͷ����Ͱ˻�ٺ��� ����)

	���� ���ͷ����� ������ erase�Լ� ����
	�ϳ� �����µ�
	����� ��������(?) ���� �ּҸ� ����Ű�� ��
	(���׸�Ʈ ����)
	��� for���̾ƴ� else���� ++vi~~�ؼ� ó��
	
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
			break; // �־�� �� ����
		}


	}


}
