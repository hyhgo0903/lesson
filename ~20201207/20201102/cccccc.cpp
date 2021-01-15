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
		cout << "맞추고 나가봥\n" << chanceCount << "회 남았다.\n입력 → : ";
		cin >> player;

		if (player < 0 || player > 999)
		{
			cout << "범위밖. 다시입력(기회차감X)";
			continue;
		}
		if (player < comNum)
		{
			cout << "그거보다 크다\n";
		}
		else if (player > comNum)
		{
			cout << "그거보다 작다\n";
		}
		else
		{
			cout << "정답\n";
			break;
		}
		if (chanceCount <= 1)
		{
			cout << "정답은 : " << comNum << endl;
			cout << "빠이~\n";
			break;
		}
		chanceCount--;
	}


	return 0;

}