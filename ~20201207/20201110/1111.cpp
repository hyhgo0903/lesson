#include <iostream>
#include "Player.h"
#include "Enemy.h"
using namespace std;
int main()
{
	Player* p1 = new Player;
	cout << "�÷��̾� ü��" << p1->getPlayerHP() << endl;
	cout << "�÷��̾� ���ݷ�" << p1->getPlayerAtk() << endl;


	Enemy* em = new Enemy;
	cout << "\n�� ü��" << em->getEnemyHP() << endl;
	cout << "�� ���ݷ�" << em->getEnemyAtk() << endl;

	cout << "\n������ �ְ� ����\n";
	em->setEnemyHP(em->getEnemyHP() - p1->getPlayerAtk());
	p1->setPlayerHP(p1->getPlayerHP() - em->getEnemyAtk());

	cout << "\n�÷��̾� ü��" << p1->getPlayerHP() << endl;
	cout << "�� ü��" << em->getEnemyHP() << endl;
	
	return 0;
}