#include <iostream>
using namespace std;

int main1242()
{
	// �ݺ��� pt2.
	//while�� : �⺻������ ���ѷ���. ���϶��� ����
/*
	while (true)
	{
		cout << "�������\n";
	}*/

	/* ��� : 
	1. return : �� ��ȯ�� ����
	2. break : (������ only) ������ �����ϰ� ��������
	3. continue : (������ only) ������ �ǳʶڴ�
	(4. go to) ������ �ǳʶپ���� .. �� �Ⱦ��µ�
	*/
	/*
	for (int i = 0; i < 5; i++)
	{
		if (i == 3) continue;
		cout << i << endl;
	}*/
	
	int num;
	int count = 5;
	while (true)
	{
		cout << "���� �����(0~9) ��ȸ "<< count <<"�� : ";
		cin >> num;
		
		if (num > 9)
		{
			cout << "���� �ٽú���\n";
			continue;
		}
		
		if (num == 8)
		{
			cout << "����\n";
			break;
		}
		else
			cout << "�װ� �ƴѵ�\n";

		count--;
	}


	return 0;
}
