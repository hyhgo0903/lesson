#include <iostream>
using namespace std;

int main1241241()
{

	 //�ݺ���, ������
	// 1. for��
	//		�ʱ�ȭ	����	(����)	����
	for (int i = 0; i < 10; i++)
	{// 0~9
		cout << i << endl;
	}// ������� ������

	for (int i = 10; i >= 0; i--)
	{// 10~0
		cout << i << endl;
	}// �������� ����

	int gugu;
	cout << "���ϴ� ���� �Է� : ";
	cin >> gugu;
	for (int i = 1; i < 10; i++)
	{
		cout << gugu << " X " << i << " = " << gugu * i << endl;
	}
	cout << endl;

	// �ݺ����ȿ� �ݺ��� ����. 2�� for��
	// but ����ӵ��� �������� �پ����..(9*9) -> Ư�� ���������� ���� �Ⱦ�
	
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			cout << i << " X " << j << " = " << i * j << endl;
		}
	}
	cout << endl;
	return 0;
}
