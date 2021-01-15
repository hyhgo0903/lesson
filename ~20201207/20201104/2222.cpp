#include <iostream>

using namespace std;

int main2()
{
	const char* star = "*****"; // 포인터 // 7칸짜리주소
	const char* space = "    ";

	cout << star + 3;
	cout << endl << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << star + i << endl;
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << star + 4 - i << endl;
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << space + 4 - i ;
		cout << star + i << endl;
	}
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << space + i ;
		cout << star + 4 - i << endl;
	}

	return 0;
}
