#include "stdafx.h"
#include "playGround.h"

//객체지향적 코딩방식이 생겨나면서
//헤더파일은 여러개의 cpp파일을 거느릴(?) 수 있는데
//게임처럼 코드량이 많은 분야에서는 
//함수별로 cpp파일을 분할해서 가독성을 높이기도 한다.
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

