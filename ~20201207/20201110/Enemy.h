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
	int getEnemyHP() { return _hp; } // 접근자 getter
	int getEnemyAtk() { return _atk; }
	void setEnemyHP(int hp) { _hp = hp; } // 설정자 setter
	// 접근자 설정자는 헤더파일에 넣는게 관례임
};