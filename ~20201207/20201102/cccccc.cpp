#include <iostream>
#include <time.h>
using namespace std;

int main_updown()
{
	srand(time(NULL));
	int comNum, chanceCount, player;
	comNum = rand() % 1000;
	chanceCount = 10;
	
	while (true)
	{
		cout << "���߰� �����g\n" << chanceCount << "ȸ ���Ҵ�.\n�Է� �� : ";
		cin >> player;

		if (player < 0 || player > 999)
		{
			cout << "������. �ٽ��Է�(��ȸ����X)";
			continue;
		}
		if (player < comNum)
		{
			cout << "�װź��� ũ��\n";
		}
		else if (player > comNum)
		{
			cout << "�װź��� �۴�\n";
		}
		else
		{
			cout << "����\n";
			break;
		}
		if (chanceCount <= 1)
		{
			cout << "������ : " << comNum << endl;
			cout << "����~\n";
			break;
		}
		chanceCount--;
	}


	return 0;

}