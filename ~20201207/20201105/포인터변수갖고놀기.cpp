#include <iostream>
#include <string>
using namespace std;


int main1412415()
{
	int * a;
	int b;

	b = 3500;
	cout << b << endl;

	a = &b;
	*a = 4500;
	cout << b << endl;

	//'캐릭터형 포인터 변수는 문자열을 저장하고 있는 게 아니라,
	//문자열이 저장 돼 있는 메모리 상의 시작 위치를 가리키고 있다.' 
	

	const char * c = "abc";
	// char * c = "abc" 는 안정성 문제로 에러가 뜬다.
	char d[10] = "abcd";
	// c(문자의 포인터변수 --- 주소값)와
	// d(배열 -> 포인터의 일종)
	// 사실상 같은 원리로 할당받은것
	cout << c << endl; // abc
	cout << *c << endl;  // a
	//c 가 리키고 있는 부분, 즉 문자열의 시작 주소 값 부터 null 문자를 만날때 까지
	cout << *(c+1) << endl; // b
	cout << &c << endl; // 주소
	cout << &"abc" << endl; // 주소

	cout << d << endl; // abc
	// 일반적인 배열과 다른점인듯
	cout << &d << endl; // 주소가 뜸
	cout << &d[0] << endl; // abc
	cout << d[0] << endl; // a
	cout << d[1] << endl; // b
	cout << d[2] << endl; // c

	string s = "abcdefghigklmnop";
	int counter[256];
	for (int i = 0; i < 256; i++)
	{
		counter[i] =0;
	}
	counter[s[2]] = 99; // s[2]인 c가 아스키코드로 들어감
	for (int i = 90; i < 120; i++)
	{
		cout << counter[i] << "  ";
	}


	return 0;
}