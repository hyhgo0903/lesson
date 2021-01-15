// #include <iostream>
#include "mainGame.h"
#include "numberBaseball.h"
#include "cardGame.h"
using namespace std;

int main222222()
{
	mainGame mg;
	mainGame mg1;
	mainGame mg2;
	// 스택은 후입선출 Last In First Out
	// 나중에 온게 첫째로 나간다.
	int a;
	// 제가 mg mg1 mg2순으로 생성자 ->> mg2 mg1 mg 순으로 소멸자
	cout << "1이나 2 입력.";
	cin >> a;
	switch (a)
	{
	case 1: {numberBaseball nb; }
		break;
	case 2: {cardGame cd; }
		break;
	}


	return 0;
}