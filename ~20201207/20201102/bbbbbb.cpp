#include <iostream>
#include <time.h>
using namespace std;

int main()
{ // 숫자야구(대신 세자리로)
	srand(time(NULL));
	int comNum1 = -1;
	int comNum2 = -1;
	int comNum3 = -1;
	int chanceCount = 10;
	int playerNum1, playerNum2, playerNum3;

	comNum1 = rand() % 9 + 1; // 1~9
	do {
		comNum2 = rand() % 10;
	} while (comNum1 == comNum2);
	do {
		comNum3 = rand() % 10;
	} while (comNum1 == comNum3 || comNum2 == comNum3);

	// cout << comNum1 << comNum2 << comNum3 << endl;
	// 테스트용으로 정답 출력
	while (1)
	{
		cout << "남은 기회는 : " << chanceCount << endl;
		cout << "세자리 숫자를 공백을 두고 입력하세요.\n";
		cout << "(첫자리는 0이 올 수 없음. 각 숫자는 중복되지 않게) : ";
		cin >> playerNum1 >> playerNum2 >> playerNum3;
		cout << endl;

		if (playerNum1 > 9 || playerNum2 > 9 || playerNum3 > 9)
		{
			cout << "범위 밖의 숫자를 입력했습니다.\n";
			cout << "세자리 숫자를 붙여서 입력하면 안 돼요 ㅠㅠ\n\n";
			continue;
		}
		if (playerNum1 == 0)
		{
			cout << "첫 자리 숫자는 0이 올 수 없음.\n\n";
			continue;
		}
		if (playerNum1 == playerNum2 || playerNum2 == playerNum3 || playerNum1 == playerNum3)
		{
			cout << "각각의 숫자가 중복되지 않도록 입력하세요.\n\n";
			continue;
		}
	
		int stCount = 0;
		int ballCount = 0;

		if (playerNum1 == comNum1)
			stCount += 1;
		if (playerNum2 == comNum2)
			stCount += 1;
		if (playerNum3 == comNum3)
			stCount += 1;

		if (playerNum1 == comNum2 || playerNum1 == comNum3)
			ballCount += 1;
		if (playerNum2 == comNum1 || playerNum2 == comNum3)
			ballCount += 1;
		if (playerNum3 == comNum1 || playerNum3 == comNum2)
			ballCount += 1;

		cout << stCount << "스트라이크 " << ballCount << "볼\n\n";		

		if (stCount == 3)
		{
			cout << "정답\n";
			break;
		}
		if (chanceCount == 1)
		{
			cout << "기회를 모조리 소진했습니다!\n";
			break;
		}
		chanceCount--;
	}

	return 0;
}