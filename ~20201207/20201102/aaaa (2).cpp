#include <iostream>
using namespace std;

int main1242()
{
	// 반복문 pt2.
	//while문 : 기본적으로 무한루프. 참일때만 동작
/*
	while (true)
	{
		cout << "꺼내줘요\n";
	}*/

	/* 제어문 : 
	1. return : 값 반환후 종료
	2. break : (루프문 only) 연산을 종료하고 빠져나감
	3. continue : (루프문 only) 연산을 건너뛴다
	(4. go to) 연산을 건너뛰어버림 .. 잘 안쓰는듯
	*/
	/*
	for (int i = 0; i < 5; i++)
	{
		if (i == 3) continue;
		cout << i << endl;
	}*/
	
	int num;
	int count = 5;
	while (true)
	{
		cout << "수를 맞춰라(0~9) 기회 "<< count <<"번 : ";
		cin >> num;
		
		if (num > 9)
		{
			cout << "범위 다시봐라\n";
			continue;
		}
		
		if (num == 8)
		{
			cout << "정답\n";
			break;
		}
		else
			cout << "그거 아닌데\n";

		count--;
	}


	return 0;
}
