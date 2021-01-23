#include <stdio.h>

int main_array(void)
{
	int sub_array[3];
	/* �������� ������ ���ÿ� ����
	 ���ȣ���� ��� ����
	 3���ϱ� [0],[1],[2]�� ���� */
	sub_array[0] = 30;
	// ���� index�� 0���� ������
	// int ������ ���������ϱ� ����X
	sub_array[1] = 40;
	sub_array[2] = 50;

	for (int i = 0; i < 3; i++)
	{
		printf("%dȣĭ�� %d���� Ÿ�� �־�\n", i + 1, sub_array[i]);
	}

	int arr[5] = { 1,3,5,7,9 };
	for (int i = 0; i < 5; i++)
	{
		printf("%d\n", arr[i]);
	}
	/* ���� �صθ� (int arr[10];ó��)
	��½ÿ� ���̰� ����
	���� ���� �ݵ�� �ʱ�ȭ�� �ؾ���

	�ٸ�, int arr[10] = {1,2}; ó��
	�ϳ��� ������ �صθ�
	���� �����ʹ� �ڵ����� 0�� �־���
	(�ϳ��� ���� ���ؾ� �����Ⱚ�� ���°�)
	*/
	
	/*
	int size = 10;
	int arr[size];
	�̷��Դ� �Ұ�. �迭ũ��� �׻� ����� �־��
	*/
	int arr2[] = { 1,3,5,7,9,11,13,15,17,19 };
	// �̷��� ���� ����. ������ ���� �������
	float arr_f[5] = { 1.2f, 2.4f, 3.5f };
	for (int i = 0; i < 5; i++)
	{
		printf("%.2f\n", arr_f[i]);
	}
	// ���� vs ���ڿ�
	char c = 'A';
	printf("%c\n", c);

	char str[7] = "coding";
	printf("%s\n", str);
	/* ���ڿ����� ���� �ǹ��ϴ� NULL����('\0;')�� ���ԵǾ����
	(���� 6�� ������ coding�ڿ� �̻��� ���ڰ� ���
		6���� ������ [c][o][d][i][n][g]����
	���ڸ� ���� ������[\0]�� �ڵ����� ��.
	*/

	char str2[] = "1234567";
	printf("%s\n", str2);
	printf("%d\n", sizeof(str2));
	/* �������� �����ϸ� �ڵ����� �����
	���ڸ� �а� NULL���ڱ����ؼ� char str2[8]�� ��������*/

	for (int i = 0; i < sizeof(str2); i++)
	{
		printf("%c\n", str2[i]);
	} // ����غ��� ������ ��ĭ ����ִµ� NULL���� �ڸ�
	char kor[] = "����ȣ";
	printf("%s\n", kor);
	printf("%d\n", sizeof(kor));
	/* ���� �ѱ��� : 1byte (= char ũ��)
	�ѱ��� 2byte�� �ʿ�.
	���� 2*3 + 1(NULL)�� 7������*/
	
	char str3[7] = { 'c','o','d','i','n','g','\0' };
	printf("%s\n", str3);

	char str4[10] = { 'c','o','d','i','n','g'};
	printf("%s\n", str4);
	for (int i = 0; i < sizeof(str4); i++)
	{
		printf("%c\n", str4[i]);
	}
	// ���°����� ������ ���ڿ����� �ڵ����� ���Ѵ�.
	// sizeof(st4)�� 10�̹Ƿ� NULL���Ե� ���� ���
	for (int i = 0; i < sizeof(str4); i++)
	{
		printf("%d\n", str4[i]);
		// ���ڿ�(char)�� ������ %d��½�
		// ASCII�ڵ尪 ��� NULL���ڴ� 0���� ���
	}

	char str5[256]; // 1prinfscanf���� �ߴ���
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf_s("%s", str5, sizeof(str5));
	printf("%s\n", str5);

	/*
	ASCII�ڵ� : ANSI(�̱�ǥ����ȸ)���� ������ ǥ���ڵ�ü��
	7bit : �� 128�� �ڵ� [0-127]
	a:97, A:65, 0:48 */

	/*for (int i = 0; i < 128; i++)
	{
		printf("�ƽ�Ű�ڵ� : %d = %c\n", i, i);
	}*/
	printf("%c\n", 'a');
	printf("%d\n", 'a');
	printf("%c\n", '\0');
	printf("%d\n", '\0');

	return 0;
}