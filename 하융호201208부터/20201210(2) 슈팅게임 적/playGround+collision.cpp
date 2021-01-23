#include "stdafx.h"
#include "playGround.h"

//객체지향적 코딩방식이 생겨나면서
//헤더파일은 여러개의 cpp파일을 거느릴(?) 수 있는데
//게임처럼 코드량이 많은 분야에서는 
//함수별로 cpp파일을 분할해서 가독성을 높이기도 한다.
void playGround::collision()
{ // 내총알이 쟤총알에
	for (int i = 0; i < _ship->getRm()->getVBullet().size(); ++i)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_em->getVMinion()[j]->getRect(),
				&_ship->getRm()->getVBullet()[i].rc))
			{
				if (_ship->getRm()->getVBullet()[i].rc.bottom < 0 ) continue;
				// 화면밖에서 있는데도 죽이길래 그거 방지
				STATE state = _em->getVMinion()[j]->getState();
				// 일딴 제거시 어느상태인지 입력받고
				_ship->getRm()->removeMissile(i);
				if (_em->getVMinion()[j]->getState() == PHASE_BOSS) continue;
				// 보스는 미사일만 지워줌
				_em->removeMinion(j);
				if (_em->getVMinion().empty())
				{ // 벡터가 비었다면 아까 받은 상태에따라서
					switch (state)
					{ // 리젠함수를 호출한다
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

