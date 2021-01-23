#pragma once
#include "gameNode.h"
#include "bullets.h"
#include <vector>
#include "minion.h"

//��ȣ������ ���� ���漱��(����ġ�ĺ���) ���� ���� *-_-*
class spaceShip;
/*
2�� ������ spaceShip�̶� enemyManager����(�� ������)

��Ŭ���� ����X(��ȣ������ ����)
playGround.init()�����Ű�µ�
spaceShip.h���� -> �����ߴ��� enemyManager.h����
-> �����ߴ��� spaceShip.h����.. (������� ���ѷ��� ����)

==> ��ȣ������ ���� ���漱��(cpp�� ����ְ� ����� ���漱���ϴµ�)
����� �� ������ ���°ͺ��� ����

*/


class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	bullet* _bullet;

	spaceShip* _ship;

public:
	enemyManager() {};
	~enemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion();

	void minionBulletFire();

	void removeMinion(int arrNum);
	// �ܺο��� ���л����ϸ� �ȵ�
	// ȣ���ؼ� ��ü ������ ����Բ��ؾ�
	// ��ü�� ������ ������ ����� �Լ� ����
	void collision();

	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getViMinion() { return _viMinion; }
	bullet* getBullet() { return _bullet; }

	void setSpaceShipMemoryAddressLink(spaceShip* ship) { _ship = ship; }
	/* ���� ���� ������� �����ϴ� _ship��
	playGround�� �� _ship���� ����
	�� _ship(�������� �ּҰ���)
	��������� �Ű����� �ּҷ� �ٲٴ� �Լ�
	(�󲮵��⿡ �ּҿ����ؼ� �� �� �ְ�)
	
	playGround�� _em->setSpaceShipMemoryAddressLink(_ship); �� ��������(�ű⼭�� _ship�� ��¥ ��)
	*/

};

