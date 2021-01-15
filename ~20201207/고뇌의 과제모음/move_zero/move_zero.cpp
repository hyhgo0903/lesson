#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));

	int board[5][5];
	int num = 0;
	int select, zeroSpacex, zeroSpacey;
	int temp2;

	for (int i = 0; i < 5; i++)
	{ // 판 채우기
		for (int j = 0; j < 5; j++)
		{
			board[i][j] = num;
			num++;
		}
	}

	// 셔플링 150번
	int temp, shuf1x, shuf1y, shuf2x, shuf2y;
	for (int i = 0; i < 150; i++)
	{
		shuf1x = rand() % 5;
		shuf1y = rand() % 5;
		shuf2x = rand() % 5;
		shuf2y = rand() % 5;
		temp = board[shuf1x][shuf1y];
		board[shuf1x][shuf1y] = board[shuf2x][shuf2y];
		board[shuf2x][shuf2y] = temp;
	}

	while (1)
	{
		system("cls");
		cout << "		0 이동시키기 \n\n";
		for (int i = 0; i < 5; i++)
		{ // 판출력
			for (int j = 0; j < 5; j++)
			{
				cout << board[i][j] << "	";
			}
			cout << "\n\n";
		}
		
		for (int i = 0; i < 5; i++)
		{ // 0어딨는지 검사
			for (int j = 0; j < 5; j++)
			{
				if (board[i][j] == 0)
				{
					zeroSpacex = i;
					zeroSpacey = j;
					break;
				}
			}
		}
		cout << "	     ↑:위로\n";
		cout << "←:왼쪽으로, ↓:아래로, →:오른쪽으로\n";
		cout << "키를 입력하세요 : ";
		select = _getch();
		if (select == 224)
		{
			select = _getch();
			if (select == 72) // 위로
			{
				if (zeroSpacex == 0) // 최상단 무효처리
				{
					continue;
				}
				else
				{
					temp2 = board[zeroSpacex - 1][zeroSpacey];
					board[zeroSpacex - 1][zeroSpacey] = 0;
					board[zeroSpacex][zeroSpacey] = temp2;
				}
			}
			else if (select == 80) // 아래로
			{
				if (zeroSpacex == 4) // 최하단 무효처리
				{
					continue;
				}
				else
				{
					temp2 = board[zeroSpacex + 1][zeroSpacey];
					board[zeroSpacex + 1][zeroSpacey] = 0;
					board[zeroSpacex][zeroSpacey] = temp2;
				}
			}
			else if (select == 75) // 왼쪽으로
			{
				if (zeroSpacey == 0) // 가장왼쪽 무효처리
				{
					continue;
				}
				else
				{
					temp2 = board[zeroSpacex][zeroSpacey - 1];
					board[zeroSpacex][zeroSpacey - 1] = 0;
					board[zeroSpacex][zeroSpacey] = temp2;
				}
			}
			else if (select == 77) // 오른쪽으로
			{
				if (zeroSpacey == 4) // 가장오른쪽 무효처리
				{
					continue;
				}
				else
				{
					temp2 = board[zeroSpacex][zeroSpacey + 1];
					board[zeroSpacex][zeroSpacey + 1] = 0;
					board[zeroSpacex][zeroSpacey] = temp2;
				}
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}

	return 0;
}