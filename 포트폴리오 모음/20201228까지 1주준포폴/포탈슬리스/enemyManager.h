#pragma once
#include "gameNode.h"
#include <vector>
#include "groundEnemy.h"
#include "flyingEnemy.h"
#include "itemManager.h" // ���ʹ�(����) ����鼭 ������ ����Լ� ȣ���ϱ� ����
#include "playerManager.h" // �÷��̾� ��ġ ����ͼ� �׿����� �׼� �ο��ϱ� ����(��������)

class bulletManager;

#define ENEMYTABLE 10 // �� ���� ����Ұ���?

class enemyManager : public gameNode
{
private:
	vector<groundEnemy*> _vGEnemy;
	vector<groundEnemy*>::iterator _viGEnemy;
	vector<flyingEnemy*> _vFEnemy;
	vector<flyingEnemy*>::iterator _viFEnemy;

	bulletManager* _bm;
	itemManager* _im;
	playerManager* _pm;
	bool _enemyTable[ENEMYTABLE];
	bool _isVictory; // ���������� ���⼭ �ϴ°� ����Ƿ�..
	// ���� �ǰ� 0���ϰ� �Ǹ� �̰� ������ �÷��̾����� ����ȯ

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void enemyUpdate();
	void createEnemy();
	void enemyFire();

	vector<groundEnemy*> getVGEnemy() { return _vGEnemy; }
	vector<groundEnemy*>::iterator getViGEnemy() { return _viGEnemy; }
	vector<flyingEnemy*> getVFEnemy() { return _vFEnemy; }
	vector<flyingEnemy*>::iterator getViFEnemy() { return _viFEnemy; }
	bool getIsVictory() { return _isVictory; }
	
	void test();	

	void setBmMemoryAddressLink(bulletManager* bm) { _bm = bm; }
	void setImMemoryAddressLink(itemManager* im) { _im = im; }
	void setPmMemoryAddressLink(playerManager* pm) { _pm = pm; }
};

