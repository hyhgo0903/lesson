#include <iostream>
using namespace std;

struct tagUnit
{
	const char * name;
	int hp;
	int atk;
};

void attack(const char* dealName, int* atk, const char* defName, int* hp)
{
	*hp -= *atk;
	cout << dealName << "�� ���� " << *atk << "�� ������\n";
	cout << defName << "�� ���� ü�� " << *hp << "\n";
	cout << endl;
}// ���ݿ��Լ�(�������̸�, &���ݺ���, �������̸�, &ü�º���);
// attack(const char* dealName, int* atk, const char* defName, int* hp)
// attack(Orc.name, &Orc.atk, Human.name, &Human.hp);

int main125125()
{
	const char* a = "abc";
	char b[10] = "abc";

	tagUnit Orc;
	tagUnit Human;

	Orc.name = "����";	Orc.hp = 100;
	Human.name = "�켭";	Human.hp = 100;


	while (Human.hp >0 && Orc.hp > 0)
	{
		Human.atk = rand() % 10;
		Orc.atk = rand() % 10;

		attack(Orc.name, &Orc.atk, Human.name, &Human.hp);
		attack(Human.name, &Human.atk, Orc.name, &Orc.hp);
	}

	return 0;
}
