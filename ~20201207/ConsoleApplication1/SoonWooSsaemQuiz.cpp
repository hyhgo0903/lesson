// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

int main_22()
{
	/*
	2 * 1 = 2		3 * 1 = 3		4 * 1 = 4 
	2 * 2 = 4       3 * 2 = 6 
	.
	.

	5				6				7

	8				9

	*/

	int count = 0;
	for (int i = 0; i < 3; i++)
	{		
		for (int k = 1; k < 10; k++)
		{
			for (int j = 2; j < 5; j++) // 3번
			{				
				if (count * 3 + j == 10)
				{
					break;
				}
				cout << count * 3 + j << " X " << k << " = " << (count * 3 + j)*k << "		";
			}
			cout << endl;

		}
		count += 1;
	}

	return 0;
}
