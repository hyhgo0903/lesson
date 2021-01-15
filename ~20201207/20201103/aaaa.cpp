#include <iostream>

using namespace std;

int main1515()
{
	char board[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = ' ';
	int nowTurn=1;
	int a, b;

	while (1)
	{
		cout << "┌─┬─┬─┐\n";
		cout << "┣" << board[0][0]
			<<"┼"<< board[1][0]<<"┼"<<
			board[2][0] <<"┤\n";
		cout << "┣─┼─┼─┤\n";
		cout << "┣" << board[0][1]
			<< "┼" << board[1][1] << "┼" <<
			board[2][1] << "┤\n";
		cout << "┣─┼─┼─┤\n";
		cout << "┣" << board[0][2]
			<< "┼" << board[1][2] << "┼" <<
			board[2][2] << "┤\n";
		cout << "└─┴─┴─┘\n";

		cout << "둘 곳을 선택하시오(0~2인 2개 수를 받습니다.)";
		cin >> a >> b;
		if (nowTurn == 1)
		{
			board[a][b] = 'O';
		}
		else
			board[a][b] = 'X';		
		nowTurn *= -1;
		cout << "턴종료\n\n";
	}

	return 0;
}
