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
		cout << "��������������\n";
		cout << "��" << board[0][0]
			<<"��"<< board[1][0]<<"��"<<
			board[2][0] <<"��\n";
		cout << "��������������\n";
		cout << "��" << board[0][1]
			<< "��" << board[1][1] << "��" <<
			board[2][1] << "��\n";
		cout << "��������������\n";
		cout << "��" << board[0][2]
			<< "��" << board[1][2] << "��" <<
			board[2][2] << "��\n";
		cout << "��������������\n";

		cout << "�� ���� �����Ͻÿ�(0~2�� 2�� ���� �޽��ϴ�.)";
		cin >> a >> b;
		if (nowTurn == 1)
		{
			board[a][b] = 'O';
		}
		else
			board[a][b] = 'X';		
		nowTurn *= -1;
		cout << "������\n\n";
	}

	return 0;
}
