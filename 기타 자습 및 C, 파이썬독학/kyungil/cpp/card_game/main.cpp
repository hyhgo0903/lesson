#include <iostream>
#include <time.h>
using namespace std;
class Game
{
public:
	int card[52];
	int myCard[3];
	int money = 1000000;
	int batting;
	int game = 0;
};
void CardPrint(int num) //카드를 출력한다.
{
	switch (num/ 13)
	{
	case 0:
		cout << "♥";
		break;
	case 1:
		cout << "♠";
		break;
	case 2:
		cout << "◆";
		break;
	case 3:
		cout << "♣";
		break;
	}
	switch (num % 13)
	{
	case 0:
		cout << '\t' << "A" << endl;
		break;
	case 10:
		cout << '\t' << "J" << endl;
		break;
	case 11:
		cout << '\t' << "Q" << endl;
		break;
	case 12:
		cout << '\t' << "K" << endl;
		break;
	default:
		cout << '\t' << (num % 13)  + 1 << endl;
		break;
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	Game now;
	for (int i = 0; i < 52; i++) now.card[i] = i; //카드를 만든다.
	int sour, dest, temp; //카드를 섞는다.
	for (int i = 0; i < 200; i++)
	{
		sour = rand() % 52;
		dest = rand() % 52;
		temp = now.card[sour];
		now.card[sour] = now.card[dest];
		now.card[dest] = temp;
	}
	while (true) //게임을 진행한다.
	{
		cout << "=============================" << endl << endl;
		cout << "게임 횟수 : " << now.game << endl;
		cout << "나의 소지금 : " << (unsigned int)now.money << endl;
		//카드를 고른다.
		for (int i = 0; i < 3; i++) now.myCard[i] = now.card[now.game * 3 + i];
		cout << "첫 번째 카드 : ";
		CardPrint(now.myCard[0]);
		cout << "두 번째 카드 : ";
		CardPrint(now.myCard[1]);
		//돈이 없거나 카드가 없으면 게임을 끝낸다.
		if (now.money < 1000 || now.game > 15) break;
		//배팅할 금액을 입력한다.
		cout << endl << "배팅할 금액을 입력하세요." << endl;
		cin >> now.batting;
		if (now.batting < 1000 || now.batting > now.money)
		{
			now.batting = 1000;
			cout << "최소 배팅금액 1000원을 배팅합니다." << endl << endl;
		}
		//세 번째 카드를 보여 준다.
		cout << "마지막 카드 : ";
		CardPrint(now.myCard[2]);
		//비교를 해서 배팅금액을 돌려준다.
		if ((now.myCard[0] % 13 < now.myCard[2] % 13 && now.myCard[1] % 13 > now.myCard[2] % 13) ||
			(now.myCard[0] % 13 > now.myCard[2] % 13 && now.myCard[1] % 13 < now.myCard[2] % 13)) //이김
		{
			now.money += now.batting;
			cout << endl << "이겼습니다. 배팅액을 얻습니다." << endl << endl;
		}
		else //짐
		{
			now.money -= now.batting;
			cout << endl << "졌습니다. 배팅액을 잃습니다." << endl << endl;
		}
		++now.game;
	}
	cout << "현재 소지금 : " << (unsigned int)now.money << endl;
	cout << "게임이 끝났습니다." << endl;
	if (now.money > 0)cout << "카드를 모두 소진! 당신의 승리입니다!" << endl;
	else cout << "당신의 패배! 개털털이가 되었습니다." << endl;
	return 0;
}