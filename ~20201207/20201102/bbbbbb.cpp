#include <iostream>
#include <time.h>
using namespace std;

int main()
{ // ���ھ߱�(��� ���ڸ���)
	srand(time(NULL));
	int comNum1 = -1;
	int comNum2 = -1;
	int comNum3 = -1;
	int chanceCount = 10;
	int playerNum1, playerNum2, playerNum3;

	comNum1 = rand() % 9 + 1; // 1~9
	do {
		comNum2 = rand() % 10;
	} while (comNum1 == comNum2);
	do {
		comNum3 = rand() % 10;
	} while (comNum1 == comNum3 || comNum2 == comNum3);

	// cout << comNum1 << comNum2 << comNum3 << endl;
	// �׽�Ʈ������ ���� ���
	while (1)
	{
		cout << "���� ��ȸ�� : " << chanceCount << endl;
		cout << "���ڸ� ���ڸ� ������ �ΰ� �Է��ϼ���.\n";
		cout << "(ù�ڸ��� 0�� �� �� ����. �� ���ڴ� �ߺ����� �ʰ�) : ";
		cin >> playerNum1 >> playerNum2 >> playerNum3;
		cout << endl;

		if (playerNum1 > 9 || playerNum2 > 9 || playerNum3 > 9)
		{
			cout << "���� ���� ���ڸ� �Է��߽��ϴ�.\n";
			cout << "���ڸ� ���ڸ� �ٿ��� �Է��ϸ� �� �ſ� �Ф�\n\n";
			continue;
		}
		if (playerNum1 == 0)
		{
			cout << "ù �ڸ� ���ڴ� 0�� �� �� ����.\n\n";
			continue;
		}
		if (playerNum1 == playerNum2 || playerNum2 == playerNum3 || playerNum1 == playerNum3)
		{
			cout << "������ ���ڰ� �ߺ����� �ʵ��� �Է��ϼ���.\n\n";
			continue;
		}
	
		int stCount = 0;
		int ballCount = 0;

		if (playerNum1 == comNum1)
			stCount += 1;
		if (playerNum2 == comNum2)
			stCount += 1;
		if (playerNum3 == comNum3)
			stCount += 1;

		if (playerNum1 == comNum2 || playerNum1 == comNum3)
			ballCount += 1;
		if (playerNum2 == comNum1 || playerNum2 == comNum3)
			ballCount += 1;
		if (playerNum3 == comNum1 || playerNum3 == comNum2)
			ballCount += 1;

		cout << stCount << "��Ʈ����ũ " << ballCount << "��\n\n";		

		if (stCount == 3)
		{
			cout << "����\n";
			break;
		}
		if (chanceCount == 1)
		{
			cout << "��ȸ�� ������ �����߽��ϴ�!\n";
			break;
		}
		chanceCount--;
	}

	return 0;
}