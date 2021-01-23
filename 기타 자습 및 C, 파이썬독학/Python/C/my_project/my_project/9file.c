#define _CRT_SECURE_NO_WARNINGS
// fopen���� ��������
// fopen_s�� �ᵵ �Ǳ��ѵ� ȣȯ�� ����
#include <stdio.h>
#define MAX 10000 // �����

int main_file(void)
{
	/*���� ����� : ���� �ҷ�����
	fputs/ fgets �� --> ���ڿ� ����, �ҷ�����
	fprintf/ fscanf �� --> ����ȭ�� �������� �а���
	printf, scanf �Լ��� %d, %s, &num �� ������ ����*/

	char line[MAX]; // == char line[10000];
	FILE* file = fopen("c:\\3DP\\test1.txt", "wb");
	/* \ �ϳ��� ������X (Ż�⹮�� \n \t...)
	���¹�� : r(read) �б�����
	w(rite) ��������. �̹� �ִ������̸� ������ �� ��������
	a(ppend) �̾��
	�ڿ��� t(text) b(binary data)*/
	if (file == NULL)
	{
		printf("���� ����\n");
		return 1; // ���α׷� ����
	}

	fputs("fputs�� �̿��ؼ� ������ ����\n", file);
	fputs("�� �������� Ȯ��\n", file);

	fclose(file); // ������ �����ϰ� ����
	// ������ ��ä �������� ������ �ս� ����.
	// ������ �׻� �ݾ��ִ� ������ ������

	FILE* file2 = fopen("c:\\3DP\\test1.txt", "rb");
	if (file2 == NULL)
	{
		printf("���� ����\n");
		return 1;
	}
	while (fgets(line, MAX, file2) != NULL)
	// line���ٰ� �����ϴ°�. ���پ�
	// fgets(����ɰ�, ������, ����)
	{
		printf("%s", line);
	}
	fclose(file2);

	int num[6] = { 0,0,0,0,0,0 }; // ��÷��ȣ
	int bonus = 0; // ���ʽ���ȣ
	char str1[MAX];
	char str2[MAX];
	FILE* file3 = fopen("c:\\3DP\\test2.txt", "wb");
	if (file3 == NULL)
	{
		printf("���� ����\n");
		return 1;
	}
	
	fprintf(file3, "%s %d %d %d %d %d %d\n",
		"��÷��ȣ:", 1, 2, 3, 4, 5, 6);
	fprintf(file3, "%s %d\n", "���ʽ���ȣ:", 7);
	// fprintf(����, ���Ĵ� printf�� ���)
	fclose(file3);

	FILE* file4 = fopen("c:\\3DP\\test2.txt", "rb");
	if (file4 == NULL)
	{
		printf("���� ����\n");
		return 1;
	}

	fscanf(file4, "%s %d %d %d %d %d %d", str1, &num[0],
		&num[1], &num[2], &num[3], &num[4], &num[5]);
	// fscanf(����, ����, �����Ұ�)
	printf("%s %d %d %d %d %d %d\n", str1, num[0],
		num[1], num[2], num[3], num[4], num[5]);

	fscanf(file4, "%s %d", str2, &bonus); // �ι�°��
	printf("%s %d\n", str2, bonus);

	return 0;
}