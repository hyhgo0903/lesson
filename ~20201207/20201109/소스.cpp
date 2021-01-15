#include <iostream>
#include "mainGame.h"

using namespace std;

int main()
{
	// 캡슐화 : 외부간섭 못 일어나게 방어

	// 컴파일러가 코드를 어떻게 받아들일지 고민해볼것. 

	mainGame mg;

	mg.attack();
	mg.attack(3);


	return 0;
}