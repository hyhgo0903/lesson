#include <iostream>
#include <string>

using namespace std;

int main()
{
	int* a;
	a = new int[2]{ 5,2 };
	cout << *a;
	return 0;
}