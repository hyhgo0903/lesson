#include <iostream>
using namespace std;

int main1241241()
{

	 //반복문, 루프문
	// 1. for문
	//		초기화	범위	(조건)	연산
	for (int i = 0; i < 10; i++)
	{// 0~9
		cout << i << endl;
	}// 어느정도 관습적

	for (int i = 10; i >= 0; i--)
	{// 10~0
		cout << i << endl;
	}// 내려오며 연산

	int gugu;
	cout << "원하는 단을 입력 : ";
	cin >> gugu;
	for (int i = 1; i < 10; i++)
	{
		cout << gugu << " X " << i << " = " << gugu * i << endl;
	}
	cout << endl;

	// 반복문안에 반복문 가능. 2중 for문
	// but 연산속도가 제곱으로 뛰어버림..(9*9) -> 특히 삼중포문은 절대 안씀
	
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			cout << i << " X " << j << " = " << i * j << endl;
		}
	}
	cout << endl;
	return 0;
}
