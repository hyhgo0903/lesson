#include "numberBaseball.h"

numberBaseball::numberBaseball()
{
	srand(time(NULL));

	int board[5][5];
	int num = 1;
	int bingoCount = 0;
	int select, sumx, sumy, sumd1, sumd2;
	int yeweo = 0; //���ܰ� ������ 1��...


	for (int i = 0; i < 5; i++)
	{ // ������ ä���
		for (int j = 0; j < 5; j++)
		{
			board[i][j] = num;
			num++;
		}
	}

	// ���ø� 150��
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
			cout << "\n\n		�Է°��� �߸��Ǿ����ϴ�!\n\n";
			yeweo = 0;
		}

		cout << "\n\n���� �� : " << bingoCount << "\n\n\n";
		for (int i = 0; i < 5; i++)
		{ // �����
			for (int j = 0; j < 5; j++)
			{
				if (board[i][j] == 100)
					cout << "#	";
				else
					cout << board[i][j] << "	";
			}
			cout << "\n\n";
		}

		cout << "���� �Է�(1~25) : ";
		cin >> select;

		if (select > 25 || select <= 0)
		{ // ������ ����ó��
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

			cout << "\n\n\n			�ڡ������մϴ�!�١�\n\n\n\n		��� ���� ���߼̽��ϴ�!\n\n";
			cout << "\n\n						-  made by �ù�25��_����ȣ\n\n\n";
			break;
		}
	}
}

numberBaseball::~numberBaseball()
{

}
