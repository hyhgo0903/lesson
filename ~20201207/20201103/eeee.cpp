#include <iostream>
#include <time.h>

using namespace std;

int main2324()
{
	srand(time(NULL));
	int level = 0;
	int count = 0;
	const int expensePerCout = 40;

	while (level != 12)
	{
		system("cls");
		cout << "���� : "<< level << "��\n";
		cout << "�õ�Ƚ�� : " << count << "\n\n";
		if (level <= 6)
		{
			if (rand() % 10 < 5)
			{
				cout << "��ȭ ����!\n\n";
				level += 1;
			}
			else
				cout << "��ȭ ����!\n\n";
		}
		else
		{
			if (rand() % 10 < 3)
			{
				cout << "��ȭ ����!\n\n";
				level += 1;
			}
			else
			{
				cout << "��ȭ ����!\n\n";
				level -= 1;
			}
		}

		count++;
		/*
		cout << "��ȭ�� �õ��մϴ�.";
		system("PAUSE");
		�������� �Ϸ��� �ּ� ����*/ 
	}


	cout << "�õ� Ƚ�� : " << count;
	return 0;
}