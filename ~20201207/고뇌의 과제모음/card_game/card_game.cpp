#include <iostream>
#include <time.h>
using namespace std;
// 보여줄때는 문자 반환
void showCharacter(int x)
{
	switch (x/13)
	{
	case 0: cout << "♥";
		break;
	case 1: cout << "◆";
		break;
	case 2: cout << "♣";
		break;
	case 3: cout << "♠";
		break;
	}
}
// 보여줄때는 0 -> A, 1 -> 2 ..., 10 -> J, 11 -> Q, 12->K
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
	// 카드세팅
	int card[52];
	for (int i = 0; i < 52; i++)
	{
		card[i] = i; // 0~51까지 숫자가 들어감
	}
	// A, 2, 3, 4, 5, ... K
	// 13으로 나눈 나머지가 0,1,2,3... ,12순
	// 0, 1, 2, 3, 4, ... 12 : 하트,, 13으로 나눈 몫 = 0
	// 13, 14, 15, ... 25 : 다이아,, 13으로 나눈 몫 = 1
	// 26, 27, 28, ... 38 : 클로버,, 13으로 나눈 몫 = 2
	// 39, 40, 41, ... 51 : 스페이드,, 13으로 나눈 몫 = 3
	
	// 셔플링 50번
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
	const int gameMax = 17; // 게임 최대 횟수

	int playerMoney = 1000000;
	const int leastBet = 10000;
	int bet;
	int showCard1, showCard2, determiningCard, temp2;
	int Card1Pow, Card2Pow, determinPow;
	
	while (playerMoney>0)
	{
		gameCount++; // 카드 꺼낼때도 사용할 예정
		if (gameCount == 17)
		{
			cout << "이번이 마지막 경기입니다! : \n\n";
		}

		// 카드를 할당
		showCard1 = card[3 * gameCount - 2];
		showCard2 = card[3 * gameCount - 1];
		determiningCard = card[3 * gameCount];

		Card1Pow = showCard1 % 13;
		Card2Pow = showCard2 % 13;
		determinPow = determiningCard % 13;
		
		system("cls");
		// ###################################################
		// CLS여기있으니 주석처리할거면 여길봐!

		cout << "	" << gameCount << "번째 게임			현재 소지금 : "
			<< playerMoney << "원\n\n";
			   
		cout << "세장의 카드를 뽑습니다. 덱에 카드는 "
			<< 52- 3*gameCount << "장 남았습니다.\n\n\n\n";


		cout << "		";

		showCharacter(showCard1);
		showNum(showCard1);

		cout << "				";

		showCharacter(showCard2);
		showNum(showCard2);
		cout << "\n\n\n\n";


		cout << "배팅할 금액을 입력하세요(최소 배팅액 10000) : ";
		cin >> bet;
		if (bet < 10000 || bet > playerMoney)
		{
			bet = 10000;
			cout << "\n배팅금액이 적거나 최대 소지금 넘게 배팅하셨습니다.\n";
			gameCount--;
			system("PAUSE");
			continue;
		}
		playerMoney -= bet;

		// 결과 출력
		cout << "\n\n		다음 카드는 ";
		showCharacter(determiningCard);
		showNum(determiningCard);
		cout << "였습니다.\n\n";

		if ((Card1Pow < determinPow && determinPow < Card2Pow)
			|| (Card1Pow > determinPow && determinPow > Card2Pow))
		{
			cout << "\n플레이어의 승리!\n\n배팅금액만큼 벌었습니다.\n\n";
			playerMoney += 2*bet;
		}
		else
		{
			cout << "\n플레이어의 패배!\n\n배팅금액을 잃습니다.\n\n";
		}


		if (gameCount == 17)
		{
			system("cls");
			cout << "\n		카드가 모두 소진되었습니다.\n\n";
			cout << "\n		최종 소지금은 " << playerMoney << "원 입니다.\n\n";
			cout << "\n				수고하셨습니다~\n\n";
			break;
		};
		if (playerMoney < 10000)
		{
			system("cls");
			cout << "\n		아뿔싸!\n\n	다음 게임을 진행할 돈이 없습니다!\n\n";
			break;
		};


		system("PAUSE");
	}


	return 0;
}
