#pragma once
#include "gameNode.h"
#include <vector>
#include "playerBullet.h"
#include "enemyBullet.h"
#include "effect.h"		// ����ǵ� �ʹ� �ɽ��ؼ� ������ ����Ʈ �ִ°ɷδٰ� �־����ϴ�

class playerManager;
class enemyManager;
#define BULLETMAX 1000 // �� �̻��̸� ���̻� ��ü�� ������ ����

class bulletManager : public gameNode
{
private:
	vector<enemyBullet*> _vEBullet;
	vector<enemyBullet*>::iterator _viEBullet;
	vector<playerBullet*> _vPBullet;
	vector<playerBullet*>::iterator _viPBullet;

	effect* _explosionEffect;
	int _bulletScore;
	float _wind;

	playerManager*	_pm;
	enemyManager*	_em;

public:
	bulletManager() {};
	~bulletManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void playerFire(int ID, float x, float y, float angle
		, float power, float damageCoefficient);
	void enemyFire(int ID, float x, float y, int left, float angle);
	
	void pBulletCollision();
	void eBulletCollision();
	void guidedMissile();

	void setPmMemoryAddressLink(playerManager* pm) { _pm = pm; }
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	int getScore() { return _bulletScore; }
	void setWind(float wind) { _wind = wind; }

	vector<enemyBullet*> getVEBullet() { return _vEBullet; }
	vector<enemyBullet*>::iterator getViEBullet() { return _viEBullet; }
	vector<playerBullet*> getVPBullet() { return _vPBullet; }
	vector<playerBullet*>::iterator getViPBullet() { return _viPBullet; }
};