#include <iostream>
#include <time.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int comNum1 = -1;
	int comNum2 = -1;
	int comNum3 = -1;
	int chanceCount = 10;
	int playerNum1, playerNum2, playerNum3, playerNum;

	comNum1 = rand() % 9 + 1;
	do {
		comNum2 = rand() % 10;
	} while (comNum1 == comNum2);
	do {
		comNum3 = rand() % 10;
	} while (comNum1 == comNum3 || comNum2 == comNum3);

	cout << comNum1 << comNum2 << comNum3 << endl;
	// �׽�Ʈ������ ���� ���
	while (1)
	{
		cout << "���� ��ȸ�� : " << chanceCount << endl;
		cout << "���ڸ� ���ڸ� �Է��ϼ���.\n";
		cout << "(ù�ڸ��� 0�� �� �� ����. �� �ڸ� ���ڴ� �ߺ����� �ʰ�) : ";
		cin >> playerNum;
		playerNum1 = playerNum / 100;
		playerNum2 = playerNum % 100 / 10;
		playerNum3 = playerNum % 10;
		cout << endl;

		if (playerNum < 100 || playerNum > 1000)
		{
			cout << "���� ���� ���ڸ� �Է��߽��ϴ�.\n\n";
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