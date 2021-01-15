#include "numberBaseball.h"

numberBaseball::numberBaseball()
{
	srand(time(NULL));

	int board[5][5];
	int num = 1;
	int bingoCount = 0;
	int select, sumx, sumy, sumd1, sumd2;
	int yeweo = 0; //예외가 있으면 1로...


	for (int i = 0; i < 5; i++)
	{ // 빙고판 채우기
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

		if (yeweo == 1)
		{
			cout << "\n\n		입력값이 잘못되었습니다!\n\n";
			yeweo = 0;
		}

		cout << "\n\n빙고 수 : " << bingoCount << "\n\n\n";
		for (int i = 0; i < 5; i++)
		{ // 판출력
			for (int j = 0; j < 5; j++)
			{
				if (board[i][j] == 100)
					cout << "#	";
				else
					cout << board[i][j] << "	";
			}
			cout << "\n\n";
		}

		cout << "숫자 입력(1~25) : ";
		cin >> select;

		if (select > 25 || select <= 0)
		{ // 범위밖 예외처리
			yeweo = 1;
			continue;
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (board[i][j] == select)
				{
					sumx = 0;
					sumy = 0;
					sumd1 = 0;
					sumd2 = 0;
					board[i][j] = 100;
					for (int k = 0; k < 5; k++)
						sumx += board[i][k];
					for (int k = 0; k < 5; k++)
						sumy += board[k][j];
					if (sumx == 500)
						bingoCount += 1;
					if (sumy == 500)
						bingoCount += 1;
					if (i == j)
					{
						for (int k = 0; k < 5; k++)
							sumd1 += board[k][k];
						if (sumd1 == 500)
							bingoCount += 1;
					}

					if (i == 4 - j)
					{
						for (int k = 0; k < 5; k++)
							sumd2 += board[4 - k][k];
						if (sumd2 == 500)
							bingoCount += 1;
					}
				}
			}
		}

		if (bingoCount == 12)
		{
			system("cls");

			cout << "\n\n\n			★☆축하합니다!☆★\n\n\n\n		모든 빙고를 맞추셨습니다!\n\n";
			cout << "\n\n						-  made by 플밍25기_하융호\n\n\n";
			break;
		}
	}
}

numberBaseball::~numberBaseball()
{

}
