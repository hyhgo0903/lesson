#include <iostream>

using namespace std;

void output(int);
//�Լ� ���漱��. �������� ����..
// ���漱���� ������? ����ġ�ĺ���
//�Ű������� ���� �־��൵ ��.


class Book
{
public :
	int page = 600;
	const char * name;

	void showPage()
	{
		cout << page << endl;
		cout << name << endl;
	}	
};

int main11()
{
	// 1. Ŭ����	2. ������ 3. �Ҹ��� 4. �������(C++)

	output(1);

	Book comeOn;
	comeOn.name = "���";
	comeOn.showPage();



	return 0;
}

void output(int x)
{
	cout << "�ұ�" << endl;
}