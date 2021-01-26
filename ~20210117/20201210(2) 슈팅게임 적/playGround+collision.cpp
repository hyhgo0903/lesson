#include "stdafx.h"
#include "playGround.h"

//��ü������ �ڵ������ ���ܳ��鼭
//��������� �������� cpp������ �Ŵ���(?) �� �ִµ�
//����ó�� �ڵ差�� ���� �о߿����� 
//�Լ����� cpp������ �����ؼ� �������� ���̱⵵ �Ѵ�.
void playGround::collision()
{ // ���Ѿ��� ���Ѿ˿�
	for (int i = 0; i < _ship->getRm()->getVBullet().size(); ++i)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->getVMinion()[j]->getRect(),
				&_ship->getRm()->getVBullet()[i].rc))
			{
				if (_ship->getRm()->getVBullet()[i].rc.bottom < 0 ) continue;
				// ȭ��ۿ��� �ִµ��� ���̱淡 �װ� ����
				STATE state = _em->getVMinion()[j]->getState();
				// �ϵ� ���Ž� ����������� �Է¹ް�
				_ship->getRm()->removeMissile(i);
				if (_em->getVMinion()[j]->getState() == PHASE_BOSS) continue;
				// ������ �̻��ϸ� ������
				_em->removeMinion(j);
				if (_em->getVMinion().empty())
				{ // ���Ͱ� ����ٸ� �Ʊ� ���� ���¿�����
					switch (state)
					{ // �����Լ��� ȣ���Ѵ�
					case PHASE_1: _em->regenMinion(0);
						break;
					case PHASE_2: _em->regenMinion(1);
						break;
					case PHASE_3: _em->regenMinion(2);
						break;
					}
				}
				break;
			}
		}
	}
	for (int i = 0; i < _em->getBullet()->getVBullet().size(); ++i)
	{
		RECT temp;
		RECT shipRc = RectMake(_ship->getShipImage()->getX(),
			_ship->getShipImage()->getY(),
			_ship->getShipImage()->getWidth(),
			_ship->getShipImage()->getHeight());		
		if (IntersectRect(&temp, &shipRc, &_em->getBullet()->getVBullet()[i].rc))
		{
			_em->getBullet()->removeBullet(i);
			break;
		}
	}
}

