#include <iostream>
using namespace std;

int main()
{
	int arr[5] = { 0,2,4,6,8 };
	cout << sizeof(int *) << endl;
	cout << sizeof(char *) << endl;
	cout << &arr[0] << endl;
	cout << arr << endl;
	cout << &arr[1] << endl;
	// 즉 배열은 (생긴것만 그렇지) 포인터로 되어 있다
	// (배열의 첫 메모리 주소를 가리킨다)
	// ☞ &arr[0] == arr
	// 주소는 16진법인듯?
	// 64bit체제에서 포인터는 8Byte, 32는 4Byte.

	cout << *arr << endl;
	cout << *(arr + 2) << endl;
	cout << *(arr + 4) << endl;
	cout << endl;

	// 배열 값을 바꾸고 싶다 -- 배열(포인터)로 바꿀수 있음
	// 그게 포인터니까..
	*arr = 5;
	*(arr+2) = 7;
	for(int i = 0; i < 5; i++)
	{
		cout << arr[i] << endl;
	}
	cout << endl;

	// 응용
	// char str[] = "abcdefghigk";
	// 이것도 배열의 종류,,, 즉 포인터
	// &str[0] == str
	// └a의 위치   └배열이자 포인터


	// 모든 배열은 포인터지만 포인터가 모두 배열은 X.
	return 0;
}
