#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"

HRESULT spaceShip::init()
{
	_ship = IMAGEMANAGER->addImage("플레이어", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);

	_missile = new missile;
	_missile->init(30, 400);
	
	_rm = new rectMissile;
	_rm->init(300, WINSIZEY);

	_currentHP = _maxHP = 100;

	_hpBar = new progressBar;
	_hpBar->init(_ship->getX(), _ship->getY() - 20, 53, 5);
	_hpBar->setGauge(_currentHP, _maxHP);

	return S_OK;
}

void spaceShip::release()
{
}

void spaceShip::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_ship->getCenterX(), _ship->getY() - 20);
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_rm->fire(_ship->getCenterX(), _ship->getY() - 20);
	}
	
	_missile->update();
	_rm->update();
	collision();

	_hpBar->setX(_ship->getX());
	_hpBar->setY(_ship->getY() - 20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();


	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		char temp[128];
		vector<string> vStr;
		// 10은 진수
		vStr.push_back(itoa(_ship->getX(), temp, 10));
		vStr.push_back(itoa(_ship->getY(), temp, 10));
		vStr.push_back(itoa(_currentHP, temp, 10));
		vStr.push_back(itoa(_maxHP, temp, 10));

		TXTDATA->txtSave("25기테스트.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("25기테스트.txt");
		// atoi : 문자열을 int로 바꾸는 함수 (a->i)
		// itoa : 반대로
		_ship->setX(atoi(vStr[0].c_str()));
		_ship->setY(atoi(vStr[1].c_str()));
		_currentHP = (atoi(vStr[2].c_str()));

	}
}

void spaceShip::render()
{
	_ship->render(getMemDC(), _ship->getX(), _ship->getY());

	_missile->render();
	_rm->render();
	_hpBar->render();
}

void spaceShip::collision()
{
	for (int i = 0; i < _rm->getVBullet().size(); i++)
	{
		for(int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp,
				&_rm->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_rm->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

}

void spaceShip::hitDamage(float damage)
{
	_currentHP -= damage;
}
