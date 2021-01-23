#pragma once
#include "gameNode.h"
#include "bullets.h"
#include <vector>
#include "minion.h"

//상호참조를 위한 전방선언(선조치후보고) 몹시 빨라 *-_-*
class spaceShip;
/*
2번 과제는 spaceShip이랑 enemyManager간만(더 직관적)

인클루드는 여기X(상호참조의 문제)
playGround.init()실행시키는데
spaceShip.h참조 -> 참조했더니 enemyManager.h참조
-> 참조했더니 spaceShip.h참조.. (헤더파일 무한루프 에러)

==> 상호참조를 위한 전방선언(cpp에 헤더넣고 헤더에 전방선언하는듯)
헤더를 다 데려와 쓰는것보다 빠름

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
	// 외부에서 갑분삭제하면 안됨
	// 호출해서 객체 스스로 지우게끔해야
	// 객체를 선언한 곳에서 지우는 함수 마련
	void collision();

	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getViMinion() { return _viMinion; }
	bullet* getBullet() { return _bullet; }

	void setSpaceShipMemoryAddressLink(spaceShip* ship) { _ship = ship; }
	/* 원래 여기 헤더에서 선언하는 _ship은
	playGround에 쓸 _ship과는 별개
	빈 _ship(선언만했지 주소값없)
	멤버변수를 매개변수 주소로 바꾸는 함수
	(빈껍데기에 주소연결해서 쓸 수 있게)
	
	playGround에 _em->setSpaceShipMemoryAddressLink(_ship); 로 연결했음(거기서의 _ship이 진짜 쉽)
	*/

};

