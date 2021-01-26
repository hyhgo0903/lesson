#include "stdafx.h"
#include "playerManager.h"
#include "itemManager.h"
#include "bulletManager.h"


void playerManager::fire()
{
	_tank.currentDelay = _tank.maxDelay; // �����̴� �ִ��	
	if (_tank.state == RIGHTATTACK || // ��������
		_tank.state == RIGHTRUN || _tank.state == RIGHTIDLE)
	{ _tank.state = RIGHTATTACK; stateChange();}
	else {_tank.state = LEFTATTACK; stateChange();}
	int ID; // ��ź������
	if (_specialCount < 2)
	{ // 0ĳ��⺻, 2�̻��ϱ⺻, 4��Ƽ�⺻, 6���ʱ⺻
		ID = 2 * _tank.type;
		_specialCount++;
	}
	else
	{ // 1ĳ��Ư��, 3�̻���Ư��, 5��ƼƯ��, 7����Ư��
		ID = 2 * _tank.type + 1;
		_specialCount = 0;
	}
	int isRight;
	if (_tank.state == LEFTATTACK) isRight = 0;	else isRight = 1;
	
	if (ID < 4) // �̷��� �ѹ�
	{_bm->playerFire(ID, _tank.rc.left + TANKWIDTH * isRight, _tank.rc.top, _tank.angle, 3.f + 0.08f * _tank.currentPower, _damageCoefficient);}
	else if (ID == 4 || ID == 6) // �̷��� ����
	{
		for (int i = 0; i < 3; i++)
		{
			_bm->playerFire(ID, _tank.rc.left + TANKWIDTH * isRight, _tank.rc.top,
				_tank.angle - 0.175 + 0.175*i, 3.f + 0.08f * _tank.currentPower, _damageCoefficient);
		}
	}
	else // �̷��� 9��
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				_bm->playerFire(ID, _tank.rc.left + TANKWIDTH * isRight, _tank.rc.top,
					_tank.angle- 0.175 + 0.175*i, 3.f + 0.08f * (_tank.currentPower - 10 + 10 * j), _damageCoefficient);
			}
		}
	}
}