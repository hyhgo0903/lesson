#pragma once
#include <iostream>
using namespace std;

class Player
{
private:
	int _hp; // ���������� "_"�ٿ��� �����س��°�(ȥ������)
	int _atk;
public:
	Player();
	~Player();
	int getPlayerHP() {	return _hp;	} // ������ getter
	// �ڷ����� ������ �����ϰ� ������

	int getPlayerAtk() { return _atk; }
	void setPlayerHP(int hp) { _hp = hp; } // ������ setter

	// ������ ������ ���Ǵ� �������(cpp����)�� �ִ°� ������
	// �Լ��� get set���̴°͵� ����
};