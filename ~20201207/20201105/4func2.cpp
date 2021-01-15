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
	cout << dealName << "의 공격 " << *atk << "의 데미지\n";
	cout << defName << "의 남은 체력 " << *hp << "\n";
	cout << endl;
}// 공격용함수(공격자이름, &공격변수, 피해자이름, &체력변수);
// attack(const char* dealName, int* atk, const char* defName, int* hp)
// attack(Orc.name, &Orc.atk, Human.name, &Human.hp);

int main125125()
{
	const char* a = "abc";
	char b[10] = "abc";

	tagUnit Orc;
	tagUnit Human;

	Orc.name = "쓰랄";	Orc.hp = 100;
	Human.name = "우서";	Human.hp = 100;


	while (Human.hp >0 && Orc.hp > 0)
	{
		Human.atk = rand() % 10;
		Orc.atk = rand() % 10;

		attack(Orc.name, &Orc.atk, Human.name, &Human.hp);
		attack(Human.name, &Human.atk, Orc.name, &Orc.hp);
	}

	return 0;
}
