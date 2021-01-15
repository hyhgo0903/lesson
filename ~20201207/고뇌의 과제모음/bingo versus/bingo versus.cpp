#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(NULL));

	int boardPlayer[5][5];
	int boardCom[5][5];
	int num = 1;
	int bingoCountPlayer = 0;
	int bingoCountCom = 0;
	int select, sumx, sumy, sumd1, sumd2, comRandx, comRandy;
	int errWarning = 0; //예외가 있으면 1로돼서 경고발생
	int comRand = 0;

	for (int i = 0; i < 5; i++)
	{ // 빙고판 채우기
		for (int j = 0; j < 5; j++)
		{
			boardPlayer[i][j] = num;
			boardCom[i][j] = num;
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
		temp = boardPlayer[shuf1x][shuf1y];
		boardPlayer[shuf1x][shuf1y] = boardPlayer[shuf2x][shuf2y];
		boardPlayer[shuf2x][shuf2y] = temp;
	}
	for (int i = 0; i < 150; i++)
	{
		shuf1x = rand() % 5;
		shuf1y = rand() % 5;
		shuf2x = rand() % 5;
		shuf2y = rand() % 5;
		temp = boardCom[shuf1x][shuf1y];
		boardCom[shuf1x][shuf1y] = boardCom[shuf2x][shuf2y];
		boardCom[shuf2x][shuf2y] = temp;
	}

	while (1)
	{
		system("cls");

		if (errWarning == 1)
		{
			cout << "\n\n		입력값이 중복되었거나 범위 밖입니다!\n\n";
			errWarning = 0;
		}

		cout << "플레이어 빙고 수 : " << bingoCountPlayer << "					컴퓨터 빙고 수 : " << bingoCountCom << "\n\n";
		cout << "어느쪽이든 빙고를 5개 완성할때까지 게임이 진행됩니다.\n\n";
		for (int i = 0; i < 5; i++)
		{ // 판출력
			for (int j = 0; j < 5; j++)
			{
				if (boardPlayer[i][j] == 100)
					cout << "♪	";
				else
					cout << boardPlayer[i][j] << "	";
			}
			cout << "		";
			for (int j = 0; j < 5; j++)
			{
				if (boardCom[i][j] == 100)
					cout << "♬	";
				else
					cout << boardCom[i][j] << "	";
			}
			cout << "\n\n";
		}

		cout << "숫자 입력(1~25) : ";
		cin >> select;


		if (select > 25 || select <= 0)
		{ // 범위밖 예외처리
			errWarning = 1;
			continue;
		}

		errWarning = 1; // 중복값 예외처리용
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (boardPlayer[i][j] == select)
					errWarning -= 1;
			} // 값이 있을때만 예외경고가 0값이 됨
		}

		if (errWarning == 1)
		{
			continue;
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (boardPlayer[i][j] == select)
				{
					sumx = 0;
					sumy = 0;
					sumd1 = 0;
					sumd2 = 0;
					boardPlayer[i][j] = 100;
					for (int k = 0; k < 5; k++)
						sumx += boardPlayer[i][k];
					for (int k = 0; k < 5; k++)
						sumy += boardPlayer[k][j];
					if (sumx == 500)
						bingoCountPlayer += 1;
					if (sumy == 500)
						bingoCountPlayer += 1;
					if (i == j)
					{
						for (int k = 0; k < 5; k++)
							sumd1 += boardPlayer[k][k];
						if (sumd1 == 500)
							bingoCountPlayer += 1;
					}

					if (i == 4 - j)
					{
						for (int k = 0; k < 5; k++)
							sumd2 += boardPlayer[4 - k][k];
						if (sumd2 == 500)
							bingoCountPlayer += 1;
					}
				}
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (boardCom[i][j] == select)
				{
					sumx = 0;
					sumy = 0;
					sumd1 = 0;
					sumd2 = 0;
					boardCom[i][j] = 100;
					for (int k = 0; k < 5; k++)
						sumx += boardCom[i][k];
					for (int k = 0; k < 5; k++)
						sumy += boardCom[k][j];
					if (sumx == 500)
						bingoCountCom += 1;
					if (sumy == 500)
						bingoCountCom += 1;
					if (i == j)
					{
						for (int k = 0; k < 5; k++)
							sumd1 += boardCom[k][k];
						if (sumd1 == 500)
							bingoCountCom += 1;
					}

					if (i == 4 - j)
					{
						for (int k = 0; k < 5; k++)
							sumd2 += boardCom[4 - k][k];
						if (sumd2 == 500)
							bingoCountCom += 1;
					}
				}
			}
		}

		while (1)
		{
			comRandx = rand() % 5;
			comRandy = rand() % 5;
			if (boardCom[comRandx][comRandy] != 100)
			{
				comRand = boardCom[comRandx][comRandy];
				break;
			}
		}

		sumx = 0;
		sumy = 0;
		sumd1 = 0;
		sumd2 = 0;
		boardCom[comRandx][comRandy] = 100;
		for (int k = 0; k < 5; k++)
			sumx += boardCom[comRandx][k];
		for (int k = 0; k < 5; k++)
			sumy += boardCom[k][comRandy];
		if (sumx == 500)
			bingoCountCom += 1;
		if (sumy == 500)
			bingoCountCom += 1;
		if (comRandx == comRandy)
		{
			for (int k = 0; k < 5; k++)
				sumd1 += boardCom[k][k];
			if (sumd1 == 500)
				bingoCountCom += 1;
		}
		if (comRandx == 4 - comRandy)
		{
			for (int k = 0; k < 5; k++)
				sumd2 += boardCom[4 - k][k];
			if (sumd2 == 500)
				bingoCountCom += 1;
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (boardPlayer[i][j] == comRand)
				{
					boardPlayer[i][j] = 100;
					sumx = 0;
					sumy = 0;
					sumd1 = 0;
					sumd2 = 0;
					boardPlayer[i][j] = 100;
					for (int k = 0; k < 5; k++)
						sumx += boardPlayer[i][k];
					for (int k = 0; k < 5; k++)
						sumy += boardPlayer[k][j];
					if (sumx == 500)
						bingoCountPlayer += 1;
					if (sumy == 500)
						bingoCountPlayer += 1;
					if (i == j)
					{
						for (int k = 0; k < 5; k++)
							sumd1 += boardPlayer[k][k];
						if (sumd1 == 500)
							bingoCountPlayer += 1;
					}

					if (i == 4 - j)
					{
						for (int k = 0; k < 5; k++)
							sumd2 += boardPlayer[4 - k][k];
						if (sumd2 == 500)
							bingoCountPlayer += 1;
					}
				}
			}
		}
	

		cout << "컴퓨터는 " << comRand << "를 선택했습니다.\n\n";
		system("PAUSE");


		if (bingoCountPlayer >= 5 || bingoCountCom >= 5)
		{
			system("cls");
			cout << "플레이어 빙고 수 : " << bingoCountPlayer << "					컴퓨터 빙고 수 : " << bingoCountCom << "\n\n\n\n";
			for (int i = 0; i < 5; i++)
			{ // 판출력
				for (int j = 0; j < 5; j++)
				{
					if (boardPlayer[i][j] == 100)
						cout << "♪	";
					else
						cout << boardPlayer[i][j] << "	";
				}
				cout << "		";
				for (int j = 0; j < 5; j++)
				{
					if (boardCom[i][j] == 100)
						cout << "♬	";
					else
						cout << boardCom[i][j] << "	";
				}
				cout << "\n\n";
			}
			if (bingoCountPlayer > bingoCountCom)
			{
				cout << "\n			★☆빙고 " << bingoCountPlayer - bingoCountCom << "개 차이를 내며 승리합니다!☆★\n\n\n";
			}
			else if (bingoCountPlayer < bingoCountCom)
			{
				cout << "\n			★☆빙고 " << bingoCountCom - bingoCountPlayer << "개 차이를 내며 패배합니다!☆★\n\n\n";
			}
			else
			{
				cout << "\n				★☆비겼습니다!☆★\n\n\n";
			}
			break;
		}		
	}
	cout << "\n\n							-  made by 플밍25기_하융호\n\n\n";
	return 0;
}