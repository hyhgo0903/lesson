#include "stdafx.h"
#include "playGround.h"

//��ü������ �ڵ������ ���ܳ��鼭
//��������� �������� cpp������ �Ŵ���(?) �� �ִµ�
//����ó�� �ڵ差�� ���� �о߿����� 
//�Լ����� cpp������ �����ؼ� �������� ���̱⵵ �Ѵ�.
void playGround::collision()
{
	for (int i = 0; i < _ship->getRm()->getVBullet().size(); ++i)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->getVMinion()[j]->getRect(),
				&_ship->getRm()->getVBullet()[i].rc))
			{
				_em->removeMinion(j);
				_ship->getRm()->removeMissile(i);
				break;
			}
		}
	}
}

