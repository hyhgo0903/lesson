#include <iostream>
#include <time.h>

using namespace std;

int main15125211251()
{
	// �迭
	// ���� ������ �������� ����
	int bullet[10]; // �迭����[�迭����]
	// bullet[0~9] bullet[10]�� ������ ����
	
	for (int i = 0; i < 10; i++)
	{
		bullet[i] = i + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << bullet[i] << "��° �Ѿ�\n";
	}
	/* bullet -> 100������� ġ��
	bullet[0] 100 + sizeof(int)*0 ������ ����
	bullet[1] 100 + sizeof(int)*1
	bullet[2] 100 + sizeof(int)*2
	bullet[3] 100 + sizeof(int)*3
	.
	.
	.	*/	   
	for (int i : bullet)
	{
		cout << i << " ";
	}
	cout << "\n";

	// ���߹迭 (<->�ܹ迭,,)
	// ���ⲯ,, �ӵ��� ���ٰ� ��(������ �ܹ迭�� �����µ�)
	int num[3][3];

	// num[0][0], [0][1] ,... [2][2]�� ���´�.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			num[i][j] = i * j + 5;
		}
	}

	int num2[] = { 0,2,3,5,15 }; // �迭����([5])�� ����� ��
	// (���Ӱ迡�� �� �Ⱦ��� �����. ���������� �˾Ƴ���..)
	int num3[10] = { 0,2,3 }; // �Ⱦ��� ��(num[3]����..�� �����Ⱚ�� �ƴ϶� 0�� ��

	// shuffle �˰���
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		num3[i] = i + 1;
	}


	int dest, sour, temp;
	for (int i = 0; i < 100; i++) // 100�� �ڸ��ٲٱ�(����)
	{
		dest = rand() % 10; // 0~9 �氹�����
		sour = rand() % 10;
		temp = num3[dest]; // << �����Ϸ��� temp�� �ʿ��ϴ�.
		//(��ǻ�ʹ� �¹ٲٱ⸦ �� �� ��)
		num3[dest] = num3[sour]; // �ڸ� �ٲٱ�
		num3[sour] = temp; // ����� �� �ֱ�
	}


	for (int i = 0; i < 10; i++)
	{
		cout << num3[i] << "\n";
	}


	return 0;
}