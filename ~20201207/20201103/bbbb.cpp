#include <iostream>
#include <time.h>
using namespace std;

int main22223()
{
	srand(time(NULL));

	int pitcher1, pitcher2, pitcher3;
	int batter1, batter2, batter3;
	int ball{ 0 };
	int st{ 0 };
	int chance{ 10 };

	while (1) // C#���� �ȵ�.
	{
		pitcher1 = rand() % 10;
		if (pitcher1 == 0) continue;
		pitcher2 = rand() % 10;
		if (pitcher2 == pitcher1) continue;
		pitcher3 = rand() % 10;
		if (pitcher3 == pitcher2 || pitcher3==pitcher1) continue;
		break;
	}

	while (true)
	{
		cout << "\n�Է�\n";
		cout << "ù��° ���� �Է� : ";
		cin >> batter1;
		cout << "�ι�° ���� �Է� : ";
		cin >> batter2;
		cout << "����° ���� �Է� : ";
		cin >> batter3;

		st = 0;
		ball = 0;

		if (pitcher1 == batter1) st++;
		if (pitcher2 == batter2) st++;
		if (pitcher3 == batter3) st++;
		if (pitcher1 == batter2) ball++;
		if (pitcher1 == batter3) ball++;
		if (pitcher2 == batter1) ball++;
		if (pitcher2 == batter3) ball++;
		if (pitcher3 == batter2) ball++;
		if (pitcher3 == batter2) ball++;

		if (st == 3)
		{
			cout << "�¸�\n";
			break;
		}

		if (st < 1 && ball < 1)
			cout << "�ƿ�\n";
		if (st>0)
			cout << st <<"��Ʈ����ũ "<< ball<< "��";
		else
			cout << ball << "��";

		chance--;
		if (chance == 0)
		{
			cout << "�й�\n";
			break;
		}
	}	

	return 0;
}
