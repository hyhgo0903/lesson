
#include <iostream>
using namespace std;

enum TEST
{
	ONE,
	TWO,
	THREE
}; // 0, 1, 2 할당
// 가독성을 좋게하는 용도


int main11()
{
	int num[3]{ 11,22,33 };

	cout << num[ONE]; // == num[0] = 1;
	num[TWO] = 2;

	for (int i = 0; i < THREE + 1; i++)
	{
		// 요런식으로 쓸수도 있어요
	}



	return 0;
}