#include <iostream>
#include <time.h>

using namespace std;

int main1212()
{
	// Casting - ����ȯ

	float moveDistance{3.3f };
	// f�Ⱥٿ��� �Ǵµ� C#���� �� �ٿ�����

	int totalDistnace = moveDistance * 4;
	cout << "�� �̵��Ÿ� : " << totalDistnace << endl;
	// 13.2�� �ƴ϶� 13���� ���. �Ҽ����� ������ ��

	// ����� ����ȯ. (int�� ���ž�) C��Ÿ���� ��
	cout << "�뷫 �̵��Ÿ� : " << (int)moveDistance << endl;

	// C++��Ÿ��
	// static_cast<��ȯ����>(����) ���� ���� ����
	// reinterpret_cast - �ð��� ������ �����غ�����
	// const_cast - const(���)���� Ǯ�����(���� ����)
	// dynamic_cast - ��Ӱ��迡�� ���� ����� (���� �ɵ�)

	int num = 65;
	cout << num << endl;
	cout << (char)num << endl; // �ƽ�Ű�ڵ�� 'A'�� 10�� 65
	cout << (int)'A' << endl;
	
	int board[2][2] = { 150 };
	cout << board[0][1] << "\n";

	int i;
	for (i = 0; i < 10; i++) {}
	cout << i << "\n";
	i = -2;
	while (++i) { cout << "����\n"; }
	int test[10];
	for (int & i : test)
	{
		i = 0;
	}
	cout << test[9];


	return 0;
}