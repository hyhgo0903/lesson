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
		cout << "현재 : "<< level << "강\n";
		cout << "시도횟수 : " << count << "\n\n";
		if (level <= 6)
		{
			if (rand() % 10 < 5)
			{
				cout << "강화 성공!\n\n";
				level += 1;
			}
			else
				cout << "강화 실패!\n\n";
		}
		else
		{
			if (rand() % 10 < 3)
			{
				cout << "강화 성공!\n\n";
				level += 1;
			}
			else
			{
				cout << "강화 실패!\n\n";
				level -= 1;
			}
		}

		count++;
		/*
		cout << "강화를 시도합니다.";
		system("PAUSE");
		수동으로 하려면 주석 해제*/ 
	}


	cout << "시도 횟수 : " << count;
	return 0;
}