#pragma once
#include <iostream>
using namespace std;

class Enemy
{
private:
	int _hp;
	int _atk;
public:
	Enemy();
	~Enemy();
	int getEnemyHP() { return _hp; } // ������ getter
	int getEnemyAtk() { return _atk; }
	void setEnemyHP(int hp) { _hp = hp; } // ������ setter
	// ������ �����ڴ� ������Ͽ� �ִ°� ������
};