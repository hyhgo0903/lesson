#include <iostream>
#include <string>

using namespace std;

int main2()
{
	int n;
	string a;
	cout << "배열 수 입력 : ";
	cin >> n;
	string * p = new string[n];
	for (int i = 0; i < n; i++)
	{
		cout << "정수를 입력하세요 : ";
		cin >> a;
		p[i] = a;
	}

	for (int i = 0; i < n; i++)
	{
		cout << p[i] << " ";
	}
	cout << "\n";
	delete[] p;

	return 0;
}