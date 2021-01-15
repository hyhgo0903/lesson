#include <iostream>
using namespace std;

void output()
{
	cout << "우리 정글은 뭐해" << endl;
}

int attack(int hp, int atk)
{
	hp -= atk;
	cout << atk << "만큼 데미지를 입힘.\n남은 체력 : "
		<< hp << endl << endl;
	return hp;
}

// 반환형 함수이름(매개변수 - parameter)
int main3333()
{
	output();
	output();
	output();

	int orcHp = 100;
	int orcAtk = 8;
	int humanHp = 50;
	int humanAtk = 3;
	// 만약 리턴값을 안쓰고 <- void attack(X,Y)
	// 또 포인터변수도 안쓰는경우:
	// 값의 갱신이 안됨. 복사하여 활용하기 때문.
	orcHp = attack(orcHp, humanAtk);
	humanHp = attack(humanHp, orcAtk);
	orcHp = attack(orcHp, humanAtk);
	humanHp = attack(humanHp, orcAtk);

	//call by value - 함수 내부에서 값을 복사해서 사용.
	//call by reference - 포인터를 이용해서 원래 값의 주소지에 접근해서 사용.
	// 빠르지만 원래 값이 변환되어 안정성▽

	return 0;
}
