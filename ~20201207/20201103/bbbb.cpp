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

	while (1) // C#에선 안됨.
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
		cout << "\n입력\n";
		cout << "첫번째 숫자 입력 : ";
		cin >> batter1;
		cout << "두번째 숫자 입력 : ";
		cin >> batter2;
		cout << "세번째 숫자 입력 : ";
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
			cout << "승리\n";
			break;
		}

		if (st < 1 && ball < 1)
			cout << "아웃\n";
		if (st>0)
			cout << st <<"스트라이크 "<< ball<< "볼";
		else
			cout << ball << "볼";

		chance--;
		if (chance == 0)
		{
			cout << "패배\n";
			break;
		}
	}	

	return 0;
}
