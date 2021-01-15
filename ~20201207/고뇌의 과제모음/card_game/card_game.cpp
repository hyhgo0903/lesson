#include <iostream>
#include <time.h>
using namespace std;
// �����ٶ��� ���� ��ȯ
void showCharacter(int x)
{
	switch (x/13)
	{
	case 0: cout << "��";
		break;
	case 1: cout << "��";
		break;
	case 2: cout << "��";
		break;
	case 3: cout << "��";
		break;
	}
}
// �����ٶ��� 0 -> A, 1 -> 2 ..., 10 -> J, 11 -> Q, 12->K
void showNum(int x)
{
	if (x % 13 == 0)
	{
		cout << "A";
	}
	else if (x % 13 == 10)
	{
		cout << "J";
	}
	else if (x % 13 == 11)
	{
		cout << "Q";
	}
	else if (x % 13 == 12)
	{
		cout << "K";
	}
	else
	{
		cout << x % 13 + 1;
	}
}
int main()
{	
	// ī�弼��
	int card[52];
	for (int i = 0; i < 52; i++)
	{
		card[i] = i; // 0~51���� ���ڰ� ��
	}
	// A, 2, 3, 4, 5, ... K
	// 13���� ���� �������� 0,1,2,3... ,12��
	// 0, 1, 2, 3, 4, ... 12 : ��Ʈ,, 13���� ���� �� = 0
	// 13, 14, 15, ... 25 : ���̾�,, 13���� ���� �� = 1
	// 26, 27, 28, ... 38 : Ŭ�ι�,, 13���� ���� �� = 2
	// 39, 40, 41, ... 51 : �����̵�,, 13���� ���� �� = 3
	
	// ���ø� 50��
	int temp, shuf1, shuf2;
	srand(time(NULL));
	for (int i = 0; i < 500; i++)
	{
		shuf1 = rand() % 52;
		shuf2 = rand() % 52;
		temp = card[shuf1];
		card[shuf1] = card[shuf2];
		card[shuf2] = temp;
	}
	
	int gameCount = 0;
	const int gameMax = 17; // ���� �ִ� Ƚ��

	int playerMoney = 1000000;
	const int leastBet = 10000;
	int bet;
	int showCard1, showCard2, determiningCard, temp2;
	int Card1Pow, Card2Pow, determinPow;
	
	while (playerMoney>0)
	{
		gameCount++; // ī�� �������� ����� ����
		if (gameCount == 17)
		{
			cout << "�̹��� ������ ����Դϴ�! : \n\n";
		}

		// ī�带 �Ҵ�
		showCard1 = card[3 * gameCount - 2];
		showCard2 = card[3 * gameCount - 1];
		determiningCard = card[3 * gameCount];

		Card1Pow = showCard1 % 13;
		Card2Pow = showCard2 % 13;
		determinPow = determiningCard % 13;
		
		system("cls");
		// ###################################################
		// CLS���������� �ּ�ó���ҰŸ� �����!

		cout << "	" << gameCount << "��° ����			���� ������ : "
			<< playerMoney << "��\n\n";
			   
		cout << "������ ī�带 �̽��ϴ�. ���� ī��� "
			<< 52- 3*gameCount << "�� ���ҽ��ϴ�.\n\n\n\n";


		cout << "		";

		showCharacter(showCard1);
		showNum(showCard1);

		cout << "				";

		showCharacter(showCard2);
		showNum(showCard2);
		cout << "\n\n\n\n";


		cout << "������ �ݾ��� �Է��ϼ���(�ּ� ���þ� 10000) : ";
		cin >> bet;
		if (bet < 10000 || bet > playerMoney)
		{
			bet = 10000;
			cout << "\n���ñݾ��� ���ų� �ִ� ������ �Ѱ� �����ϼ̽��ϴ�.\n";
			gameCount--;
			system("PAUSE");
			continue;
		}
		playerMoney -= bet;

		// ��� ���
		cout << "\n\n		���� ī��� ";
		showCharacter(determiningCard);
		showNum(determiningCard);
		cout << "�����ϴ�.\n\n";

		if ((Card1Pow < determinPow && determinPow < Card2Pow)
			|| (Card1Pow > determinPow && determinPow > Card2Pow))
		{
			cout << "\n�÷��̾��� �¸�!\n\n���ñݾ׸�ŭ �������ϴ�.\n\n";
			playerMoney += 2*bet;
		}
		else
		{
			cout << "\n�÷��̾��� �й�!\n\n���ñݾ��� �ҽ��ϴ�.\n\n";
		}


		if (gameCount == 17)
		{
			system("cls");
			cout << "\n		ī�尡 ��� �����Ǿ����ϴ�.\n\n";
			cout << "\n		���� �������� " << playerMoney << "�� �Դϴ�.\n\n";
			cout << "\n				�����ϼ̽��ϴ�~\n\n";
			break;
		};
		if (playerMoney < 10000)
		{
			system("cls");
			cout << "\n		�ƻԽ�!\n\n	���� ������ ������ ���� �����ϴ�!\n\n";
			break;
		};


		system("PAUSE");
	}


	return 0;
}
