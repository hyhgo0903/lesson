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
	// ������ ���Լ��� Last In First Out
	// ���߿� �°� ù°�� ������.
	int a;
	// ���� mg mg1 mg2������ ������ ->> mg2 mg1 mg ������ �Ҹ���
	cout << "1�̳� 2 �Է�.";
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