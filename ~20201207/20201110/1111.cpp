#include <iostream>
#include "Player.h"
#include "Enemy.h"
using namespace std;
int main()
{
	Player* p1 = new Player;
	cout << "플레이어 체력" << p1->getPlayerHP() << endl;
	cout << "플레이어 공격력" << p1->getPlayerAtk() << endl;


	Enemy* em = new Enemy;
	cout << "\n적 체력" << em->getEnemyHP() << endl;
	cout << "적 공격력" << em->getEnemyAtk() << endl;

	cout << "\n공격을 주고 받음\n";
	em->setEnemyHP(em->getEnemyHP() - p1->getPlayerAtk());
	p1->setPlayerHP(p1->getPlayerHP() - em->getEnemyAtk());

	cout << "\n플레이어 체력" << p1->getPlayerHP() << endl;
	cout << "적 체력" << em->getEnemyHP() << endl;
	
	return 0;
}