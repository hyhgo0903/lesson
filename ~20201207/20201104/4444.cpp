#include <iostream>
#include <string>

using namespace std;

int main444()
{
	// ���ڿ� �Լ�
	// 1. strlen == string length ���Ӹ�
	// ���ڿ� ���̸� ������ ��ȯ

	char name[6] = "teemo";
	char name2[10] = "teemo";
	
	int num = strlen(name);
	int num2 = strlen(name2);

	cout << "���ڿ� ���� : " << num << endl;
	cout << "���ڿ� ���� : " << num2 << endl;
	// name�迭��ü ũ�⸦ �д°� �ƴ�

	// 2. strcmp == string compare ���Ӹ�
	// ���ڿ� ũ�⸦ ���Ͽ� ������ 0,
	// ������ ũ�� 1, �������� ũ�� -1�� ��ȯ

	char str1[10] = "abc";
	char str2[10] = "def";
	num = strcmp(str1, str2);
	cout << "��� ���� : " << num << endl;

	// 3. strcat
	// ���ڿ� �̾���̱�
	// strcat(���ڿ�1,���ڿ�2)
	// ��, ���ڿ� 1�� ���ڿ�2��
	//�޾��ٸ�ŭ ���۰� �־��

	char str3[128] = "home ";
	char str4[50] = "sweet home";
	// strcat(str3, str4); �䷯�� �������.
	strcat_s(str3, str4);

	cout << str3 << endl;

	// 4. strcpy == string copy�� ���Ӹ�
	// strcpy(���ڿ�1,���ڿ�2)
	// ���ڿ�1�� 2�� �����Ѵ�.
	char str5[10];
	char str6[10] = "sorsor";

	strcpy_s(str5, str6);

	cout << str5 << endl;

	char str7[128];
	/*
	cout << "�Է� : ";
	cin >> str7;
	for (int i = strlen(str7); i >= 0; i--)
	{
		cout << str7[i];
	}*/

	// 1. ���ڿ��� �Է¹޾Ƽ� ¦������ ���ڸ� ���������.
	// ex ) a b c d e -> a d c b e
	// ex2) a b c d e f -> a f c d e b

	char strQuiz[128];
	cout << "�Է� : ";
	cin >> strQuiz;

	for (int i = 0; i < strlen(strQuiz); i++)
	{
		if (i % 2 == 1) // 1,3,5,7,9... ->   
		{
			cout << strQuiz[strlen(strQuiz)/2*2 - i];
			// why? : ������ 2������ 2���ϴ� ������ �ϸ� Ȧ���� ��� �˾Ƽ� 1�� ����
			// ������ : cout << strQuiz[strlen(strQuiz) - i - (strlen(strQuiz)%2)];
		}
		else
		{
			cout << strQuiz[i];
		}
	}



	cout << endl << endl;
	// 2. strtok_s <-- �����غ�����.
	// ���ڿ����� ������ ���ڷ� ���ڿ��� �и�.
	char ���ڿ�[] = "abc,etqef,jnonjfbghi";
	char ������[] = ","; // ������
	char *�����������;
	char *��������ū = strtok_s(���ڿ�,������, &�����������);

	while (����������� != NULL)
	{

	}
	cout << *��������ū << endl;
	��������ū = strtok_s(NULL, ������, &�����������);

	// �� ���ڿ��� �״�� ���Ÿ� NULL
	cout << *��������ū << endl;
	��������ū = strtok_s(NULL, ������, &�����������);
	cout << *��������ū << endl;
	//3. 
	// ������ ���� _getch()

	//scanf()
	//gets()
	//cin.ignore()
	//cin.getline()

	return 0;
}
