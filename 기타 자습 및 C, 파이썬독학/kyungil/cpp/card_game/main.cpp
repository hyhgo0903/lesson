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
void CardPrint(int num) //ī�带 ����Ѵ�.
{
	switch (num/ 13)
	{
	case 0:
		cout << "��";
		break;
	case 1:
		cout << "��";
		break;
	case 2:
		cout << "��";
		break;
	case 3:
		cout << "��";
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
	for (int i = 0; i < 52; i++) now.card[i] = i; //ī�带 �����.
	int sour, dest, temp; //ī�带 ���´�.
	for (int i = 0; i < 200; i++)
	{
		sour = rand() % 52;
		dest = rand() % 52;
		temp = now.card[sour];
		now.card[sour] = now.card[dest];
		now.card[dest] = temp;
	}
	while (true) //������ �����Ѵ�.
	{
		cout << "=============================" << endl << endl;
		cout << "���� Ƚ�� : " << now.game << endl;
		cout << "���� ������ : " << (unsigned int)now.money << endl;
		//ī�带 ����.
		for (int i = 0; i < 3; i++) now.myCard[i] = now.card[now.game * 3 + i];
		cout << "ù ��° ī�� : ";
		CardPrint(now.myCard[0]);
		cout << "�� ��° ī�� : ";
		CardPrint(now.myCard[1]);
		//���� ���ų� ī�尡 ������ ������ ������.
		if (now.money < 1000 || now.game > 15) break;
		//������ �ݾ��� �Է��Ѵ�.
		cout << endl << "������ �ݾ��� �Է��ϼ���." << endl;
		cin >> now.batting;
		if (now.batting < 1000 || now.batting > now.money)
		{
			now.batting = 1000;
			cout << "�ּ� ���ñݾ� 1000���� �����մϴ�." << endl << endl;
		}
		//�� ��° ī�带 ���� �ش�.
		cout << "������ ī�� : ";
		CardPrint(now.myCard[2]);
		//�񱳸� �ؼ� ���ñݾ��� �����ش�.
		if ((now.myCard[0] % 13 < now.myCard[2] % 13 && now.myCard[1] % 13 > now.myCard[2] % 13) ||
			(now.myCard[0] % 13 > now.myCard[2] % 13 && now.myCard[1] % 13 < now.myCard[2] % 13)) //�̱�
		{
			now.money += now.batting;
			cout << endl << "�̰���ϴ�. ���þ��� ����ϴ�." << endl << endl;
		}
		else //��
		{
			now.money -= now.batting;
			cout << endl << "�����ϴ�. ���þ��� �ҽ��ϴ�." << endl << endl;
		}
		++now.game;
	}
	cout << "���� ������ : " << (unsigned int)now.money << endl;
	cout << "������ �������ϴ�." << endl;
	if (now.money > 0)cout << "ī�带 ��� ����! ����� �¸��Դϴ�!" << endl;
	else cout << "����� �й�! �������̰� �Ǿ����ϴ�." << endl;
	return 0;
}