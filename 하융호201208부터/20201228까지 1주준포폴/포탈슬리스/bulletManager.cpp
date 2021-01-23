#include "stdafx.h"
#include "bulletManager.h"
#include "playerManager.h"
#include "enemyManager.h"

HRESULT bulletManager::init()
{
	_explosionEffect = new effect;
	_explosionEffect->init(IMAGEMANAGER->findImage("����"), 32, 62, 1, 0.5f);
	EFFECTMANAGER->addEffect("explosion", "image/explosion.bmp", 832, 62, 32, 62, 1.0f, 0.3f, 300);
	_bulletScore = 0;
	_wind = 0.f;
	return S_OK;
}

void bulletManager::release()
{
	_vEBullet.clear();	_vPBullet.clear();
	SAFE_RELEASE(_explosionEffect)
	SAFE_DELETE(_explosionEffect);
}

void bulletManager::update()
{
	pBulletCollision();
	eBulletCollision();
	guidedMissile();
	EFFECTMANAGER->update();
	_explosionEffect->update();
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		_vEBullet[i]->update(); // ������Ʈ �����ֱ���
		_vEBullet[i]->setWind(_wind); // �ٶ��Է�
	}
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		_vPBullet[i]->update(); // ������Ʈ �����ֱ���
		_vPBullet[i]->setWind(_wind); // �ٶ��Է�
	}
	bool recheck;
	recheck = true;
	while (recheck)
	{
		recheck = false;// �������̾� ������ �����ϰ� false�λ��·� �ݺ����� ������
		for (int i = 0; i < _vEBullet.size(); ++i)
		{
			if (!(_vEBullet[i]->getIsFire()))
			{ // �������̾ �����ٸ� �����ش�
				SAFE_RELEASE(_vEBullet[i]);
				SAFE_DELETE(_vEBullet[i]);
				_vEBullet.erase(_vEBullet.begin() + i);
				recheck = true; // �ݺ��� �߰��� �����Ÿ� ��üũ������Ѵ�.
				break;
			}
		}
	}
	recheck = true;
	while (recheck)
	{
		recheck = false;// �������̾� ������ �����ϰ� false�λ��·� �ݺ����� ������
		for (int i = 0; i < _vPBullet.size(); ++i)
		{
			if (!(_vPBullet[i]->getIsFire()))
			{ // �������̾ �����ٸ� �����ش�
				SAFE_RELEASE(_vPBullet[i]);
				SAFE_DELETE(_vPBullet[i]);
				_vPBullet.erase(_vPBullet.begin() + i);
				recheck = true;
				break;
			}
		}
	}	
}

void bulletManager::render()
{
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		_vEBullet[i]->render();
	}
	for (int i = 0; i < _vPBullet.size(); ++i)
	{
		_vPBullet[i]->render();
	}
	EFFECTMANAGER->render();
	_explosionEffect->render();
}

void bulletManager::playerFire(int ID, float x, float y, float angle, float power, float damageCoefficient)
{
	if (_vPBullet.size() >= BULLETMAX) return;
	playerBullet* pbullet;
	pbullet = new playerBullet;
	pbullet->init(ID, x, y, angle, power, damageCoefficient);
	_vPBullet.push_back(pbullet);
}

void bulletManager::enemyFire(int ID, float x, float y, int left, float angle)
{
	if (_vEBullet.size() >= BULLETMAX) return;
	enemyBullet* ebullet;
	ebullet = new enemyBullet;
	ebullet->init(ID, x, y, left, angle);
	_vEBullet.push_back(ebullet);
}