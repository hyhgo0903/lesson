#include <iostream>
using namespace std;

void output()
{
	cout << "�츮 ������ ����" << endl;
}

int attack(int hp, int atk)
{
	hp -= atk;
	cout << atk << "��ŭ �������� ����.\n���� ü�� : "
		<< hp << endl << endl;
	return hp;
}

// ��ȯ�� �Լ��̸�(�Ű����� - parameter)
int main3333()
{
	output();
	output();
	output();

	int orcHp = 100;
	int orcAtk = 8;
	int humanHp = 50;
	int humanAtk = 3;
	// ���� ���ϰ��� �Ⱦ��� <- void attack(X,Y)
	// �� �����ͺ����� �Ⱦ��°��:
	// ���� ������ �ȵ�. �����Ͽ� Ȱ���ϱ� ����.
	orcHp = attack(orcHp, humanAtk);
	humanHp = attack(humanHp, orcAtk);
	orcHp = attack(orcHp, humanAtk);
	humanHp = attack(humanHp, orcAtk);

	//call by value - �Լ� ���ο��� ���� �����ؼ� ���.
	//call by reference - �����͸� �̿��ؼ� ���� ���� �ּ����� �����ؼ� ���.
	// �������� ���� ���� ��ȯ�Ǿ� ��������

	return 0;
}
