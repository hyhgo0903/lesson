#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 10000
int main_file_project(void)
{
	// fgets fputsȰ��
	char line[MAX]; // ���Ͽ��� �ҷ��� ������ ����
	char contents[MAX]; // �Է��� ����
	char password[20]; // ��й�ȣ �Է�
	char c; // ��й�ȣ �Է��Ҷ� Ű�� Ȯ�ο�(******)

	printf("�ϱ�\n");
	printf("��й�ȣ �Է��ϼ���(hyh) : ");

	// getchar()/ getch()�� ����
	// getchar() : ���͸� �Է¹޾ƾ� ����
	// getch() : Ű�Է½� �ٷιٷ� ����

	int i = 0;
	while (1)
	{
		c = getch();
		if (c == 13) // enter�Է½�. �Է�����
		{
			password[i] = '\0'; // ���ڿ����� NULL����
			// ���ڿ��� �ƴ϶�
			// ���ں��� ������ �ҹ��ڷ� �ؾߵǴ°� ����
			break;
		}
		else // ��й�ȣ �Է� ��
		{
			printf("*");
			password[i] = c;
		}
		i++;
	}
	//��й�ȣ : "hyh"
	printf("\n\n=====��й�ȣ Ȯ�� ��=====\n\n");
	if (strcmp(password, "hyh") == 0)
	//��Ʈ��������Լ�: ���ڰ� �񱳴��� ������
	//0�̸� ��ġ. ����ġ�� ���ڿ�ũ�⿡���� +1,-1���
	{
		printf("\n=====��й�ȣ Ȯ�� �Ϸ�=====\n\n");
		char* fileName = "c:\\3DP\\diary.txt";
		FILE* file = fopen(fileName, "a+b");
		// a+b�� ������ ������ �����ϰ�
		// ������ append �̾��(�ڿ� ������ �߰�)
		if (file == NULL)
		{
			printf("\n=====���� ���� ����=====\n\n");
			return 1;
		}

		while (fgets(line, MAX, file) != NULL)
		{
			printf("%s", line);
		}

		printf("\n\n ������ ��� �ۼ��ϼ���!\n");
		printf("�����Ϸ��� EXIT�Է�\n");

		while (1)
		{
			scanf("%[^\n]", contents);
			// �ٹٲ�(\n)�� ������ ������ ��� ���ڿ���
			// �о���̶�� �ǹ� (�� �پ�)
			getchar(); // Enter�Է�(\n)�� Flushó��(���ش�)

			if (strcmp(contents, "EXIT") == 0)
			{
				printf("�Է��� �����մϴ�.\n\n");
				break;
			}
			fputs(contents, file);
			fputs("\n", file); // enter�� ����ó�������Ƿ�
		}
		fclose(file);
	}
	else
	{
		printf("��й�ȣ�� Ʋ����� ���Ҿ�.\n\n");
	}	

	return 0;
}