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

	//'ĳ������ ������ ������ ���ڿ��� �����ϰ� �ִ� �� �ƴ϶�,
	//���ڿ��� ���� �� �ִ� �޸� ���� ���� ��ġ�� ����Ű�� �ִ�.' 
	

	const char * c = "abc";
	// char * c = "abc" �� ������ ������ ������ ���.
	char d[10] = "abcd";
	// c(������ �����ͺ��� --- �ּҰ�)��
	// d(�迭 -> �������� ����)
	// ��ǻ� ���� ������ �Ҵ������
	cout << c << endl; // abc
	cout << *c << endl;  // a
	//c �� ��Ű�� �ִ� �κ�, �� ���ڿ��� ���� �ּ� �� ���� null ���ڸ� ������ ����
	cout << *(c+1) << endl; // b
	cout << &c << endl; // �ּ�
	cout << &"abc" << endl; // �ּ�

	cout << d << endl; // abc
	// �Ϲ����� �迭�� �ٸ����ε�
	cout << &d << endl; // �ּҰ� ��
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
	counter[s[2]] = 99; // s[2]�� c�� �ƽ�Ű�ڵ�� ��
	for (int i = 90; i < 120; i++)
	{
		cout << counter[i] << "  ";
	}


	return 0;
}